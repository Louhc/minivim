#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "minivim.h"
using std::string;
using std::vector;

#define REG_COLOR_NUM 1
#define CUS_COLOR_NUM 2

extern WINDOW *txtwin, *infowin, *cmdwin;

node::node():x(0), y(0){}
node::node( int a, int b ):x(a), y(b){}
int max( int x, int y ){ return x > y ? x : y; }
int min( int x, int y ){ return x < y ? x : y; }

node textfile::getPos( int mode, int tx, int ty ){
    ty = max(min(ty, (int)text[tx].size() - (mode == NORMAL_MODE)), 0);
    node r(-1, 0);
    for ( int i = 0; i < tx; ++i )
        r.x += ((int)text[i].size() - 1) / win_col + 1;
    r.x += ty / win_col + 1; r.y = ty % win_col;
    return r;
}

string textfile::getNthLine( int n ){
    for ( int i = 0; i < (int)text.size(); ++i ){
        if ( text[i].size() >= n * win_col )
            return text[i].substr(n * win_col, min(win_col, (int)text[i].size() - n * win_col));
        n -= ((int)text[i].size() - 1) / win_col + 1;
    }
    return "";
}

void textfile::refresh( int mode ){
    // refresh the info window
    wclear(infowin);
    if ( mode == INSERT_MODE ) wmove(infowin, 0, 0), wprintw(infowin, "-- INSERT --");
    wmove(infowin, 0, COLS - 17);
    if ( text[x].size() == 0 ) wprintw(infowin, "%d,0-1", x);
    else wprintw(infowin, "%d,%d", x, y);
    wrefresh(infowin);

    // refresh the text window
    wclear(txtwin);
    for ( int i = 0; i < win_row; ++i ){
        wmove(txtwin, i, 0);
        wprintw(txtwin, "%s", getNthLine(ul + i).c_str());
    }
    node t(getPos(mode, x, y));
    wmove(txtwin, t.x - ul, t.y);
    wrefresh(txtwin);
}

textfile::textfile(){
    text.push_back("");
    ul = x = y = 0;
    is_changed = 0;
    refresh(NORMAL_MODE);
}

textfile::textfile( string fname ){
    filename = fname;
    ul = x = y = 0;
    is_changed = 0;

    std::ifstream fin(fname);
    if ( !fin.is_open() ){
        text.push_back("");
        return;
    }

    string s;
    while( !fin.eof() ){
        std::getline(fin, s);
        text.push_back(s);
    }
    refresh(NORMAL_MODE);
}

void textfile::save(){
    std::ofstream fout(filename);
    if ( !fout.is_open() ) return;
    for ( int i = 0; i < text.size(); ++i )
        fout << text[i] + "\n";
    is_changed = 0;
}