#include <ncurses.h>
#include "minivim.h"

void NormalMode( textfile *txt ){
    int ch;
    while ( 1 ){
        ch = getch();
        switch( ch ){
            case KEY_UP:
                txt->go_up(NORMAL_MODE);
                break;
            case KEY_DOWN:
                txt->go_down(NORMAL_MODE);
                break;
            case KEY_LEFT:
                txt->go_left(NORMAL_MODE);
                break;
            case KEY_RIGHT:
                txt->go_right(NORMAL_MODE);
                break;
            case ':':
                if ( CommandMode(txt) ) return;
                break;
            case 'i':
                InsertMode(txt);
                txt->insert_to_normal();
                break;
        }

    }
}