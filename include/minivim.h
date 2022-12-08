#ifndef _MINIVIM_H
#define _MINIVIM_H

#include <vector>
#include <string>
#include <ncurses.h>
using std::vector;
using std::string;

#define win_col (COLS - 3)
#define win_row (LINES - 2)
#define NORMAL_MODE 0
#define INSERT_MODE 1

struct node{
    int x, y;
    node();
    node( int, int );
};

int max( int, int );
int min( int, int );

class textfile{
    private:
        vector<string> text;
        vector<string> old_text;
        string filename;
        int x, y, ul, tx, ty;
        bool readonly_on;
        bool truncate_on;

        node getPos( int, int, int );
        string getNthLine( int, int &, int & );
    public:
        void refresh( int ); // refresh the window. If in insert_mode, use refresh(1)
        textfile( string, bool, bool );
        bool save( string );
        void insert_to_normal();
        void go_up( int );
        void go_down( int );
        void go_left( int );
        void go_right( int );
        void backspace();
        void enter();
        void insert( char );
        void deleteline();
        bool is_changed();
        bool is_read_only();
        bool is_truncate();
        void replace( string, string );
        void jump( int );
};

void NormalMode( textfile* );
int CommandMode( textfile* );
void InsertMode( textfile* );

#endif
