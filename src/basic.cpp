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

extern WINDOW *txtwin, *infowin, *cmdwin, *lnwin;

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

string textfile::getNthLine( int n, int &t1, int &t2 ){
    for ( int i = 0; i < (int)text.size(); ++i ){
        if ( text[i].size() >= n * win_col ){
            t1 = n; t2 = i;
            return text[i].substr(n * win_col, min(win_col, (int)text[i].size() - n * win_col));
        }
        n -= ((int)text[i].size() - 1) / win_col + 1;
    }
    t1 = t2 = -1;
    return "";
}

void textfile::refresh( int mode ){
    // refresh the info window
    werase(infowin);
    if ( mode == INSERT_MODE ) wmove(infowin, 0, 0), wprintw(infowin, "-- INSERT --");
    wmove(infowin, 0, COLS - 17);
    if ( text[x].size() == 0 ) wprintw(infowin, "%d,0-1", x + 1);
    else wprintw(infowin, "%d,%d", x + 1, y);
    wrefresh(infowin);

    // refresh the text window
    werase(txtwin); werase(lnwin);
    for ( int i = 0; i < win_row; ++i ){
        wmove(txtwin, i, 0); wmove(lnwin, i, 0);
        int t1, t2;
        wprintw(txtwin, "%s", getNthLine(ul + i, t1, t2).c_str());
        if ( t1 == 0 ) wprintw(lnwin, "%d", t2 + 1);
    }
    wrefresh(lnwin);
    node t(getPos(mode, x, y));
    wmove(txtwin, t.x - ul, t.y);
    wrefresh(txtwin);
}

textfile::textfile( string fname, bool flg1, bool flg2 ){
    filename = fname;
    ul = x = y = 0;
    readonly_on = flg1;
    truncate_on = flg2;

    if ( fname == "" || is_truncate() ){
        text.push_back("");
        old_text = text;
        refresh(NORMAL_MODE);
        return;
    }

    std::ifstream fin(fname);
    if ( !fin.is_open() ){
        text.push_back("");
        old_text = text;
        refresh(NORMAL_MODE);
        return;
    }

    string s;
    while( !fin.eof() ){
        std::getline(fin, s);
        if ( s.size() > 0 && s[s.size() - 1] == '\r' ) s.pop_back();
        text.push_back(s);
    }
    old_text = text;
    refresh(NORMAL_MODE);
}

bool textfile::save( string fname ){
    if ( fname != "" ) filename = fname;
    if ( filename == "" ){
        werase(infowin);
        wprintw(infowin, "No file name.");
        wrefresh(infowin);
        return 0;
    }
    std::ofstream fout(filename);
    if ( !fout.is_open() ){
        werase(infowin);
        wprintw(infowin, "Unable to open %s.", filename.c_str());
        wrefresh(infowin);
        return 0;
    }
    old_text = text;
    for ( int i = 0; i < text.size(); ++i )
        if ( i + 1 == text.size() ) fout << text[i];
        else fout << text[i] + '\n';
    werase(infowin);
    wprintw(infowin, "%s saved successfully.", filename.c_str());
    wrefresh(infowin);
    return 1;
}

bool textfile::is_changed(){
    if ( text.size() != old_text.size() ) return 1;
    for ( int i = 0; i < text.size(); ++i )
        if ( text[i] != old_text[i] )
            return 1;
    return 0;
}

bool textfile::is_read_only(){
    if ( !readonly_on ) return 0;
    werase(infowin);
    wprintw(infowin, "Unable to modify a read_only file!");
    wrefresh(infowin);
    getch();
    return 1;
}

bool textfile::is_truncate(){
    return truncate_on;
}