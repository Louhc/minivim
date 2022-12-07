#include <ncurses.h>
#include "minivim.h"

extern WINDOW *txtwin, *infowin, *cmdwin;

void textfile::go_up( int mode ){
    if ( x <= 0 ) return;
    --x; ul = min(ul, getPos(mode, x, 0).x);
    refresh(mode);
}

void textfile::go_down( int mode ){
	if ( x + 1 >= text.size() ) return;
    ++x; ul = max(ul, getPos(mode, x, (int)text[x].size() - 1).x - win_row + 1);
    refresh(mode);
}

void textfile::go_left( int mode ){
    y = min(y, (int)text[x].size() - (mode == NORMAL_MODE ? 1 : 0));
    if ( y <= 0 ) return;
    --y; refresh(mode);
}

void textfile::go_right( int mode ){
    y = min(y, (int)text[x].size() - (mode == NORMAL_MODE ? 1 : 0));
    if ( y + 1 > (int)text[x].size() - (mode == NORMAL_MODE ? 1 : 0) ) return;
    ++y; refresh(mode);
}

void textfile::insert_to_normal(){
    y = min(y, max((int)text[x].size() - 1, 0));
    wclear(infowin);
    wmove(infowin, 0, COLS - 17);
    wprintw(infowin, "%d,%d", x, y);
    wrefresh(infowin);
    node t(getPos(NORMAL_MODE, x, y));
    wmove(txtwin, t.x - ul, t.y);
    wrefresh(txtwin);
}

void textfile::backspace(){
    y = min(y, (int)text[x].size());
    if ( y == 0 ){
        if ( x == 0 ) return;
        ul = min(ul, getPos(INSERT_MODE, x - 1, 0).x);
        y = text[x - 1].size();
        text[x - 1] += text[x];
        for ( int i = x; i < (int)text.size() - 1; ++i )
            text[i] = text[i + 1];
        text.pop_back(); --x;
    } else {
        if ( y == text[x].size() )
            text[x].pop_back(), --y;
        else
            text[x] = text[x].substr(0, y - 1) + text[x].substr(y, (int)text[x].size() - y), --y;
    }
    refresh(INSERT_MODE);
}

void textfile::enter(){
    y = min(y, (int)text[x].size());
    text.push_back("");
    for ( int i = (int)text.size() - 2; i >= x + 1; --i )
        text[i + 1] = text[i];
    if ( y == text[x].size() )
        text[x + 1] = "";
    else
        text[x + 1] = text[x].substr(y, (int)text.size() - y),
        text[x] = text[x].substr(0, y);
    ++x; y = 0;
    ul = max(ul, getPos(INSERT_MODE, x, (int)text[x].size() - 1).x - win_row + 1);
    refresh(INSERT_MODE);
}

void textfile::insert( char ch ){
    y = min(y, (int)text[x].size());
    if ( y == text[x].size() )
        text[x].push_back(ch);
    else
        text[x] = text[x].substr(0, y) + ch + text[x].substr(y, text[x].size() - y);
    ++y;
    ul = max(ul, getPos(INSERT_MODE, x, (int)text[x].size() - 1).x - win_row + 1);
    refresh(INSERT_MODE);
}

void textfile::deleteline(){
    for ( int i = x; i <= (int)text.size() - 2; --i )
        text[i] = text[i + 1];
    text[x].pop_back();
    y = 0; x = min(x, (int)text.size() - 1);
    ul = max(ul, getPos(INSERT_MODE, x, (int)text[x].size() - 1).x - win_row + 1);
    refresh(NORMAL_MODE);
}