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
                txt->refresh(NORMAL_MODE);
                break;
            case 'i':
                if ( !(txt->is_read_only()) ){
                    InsertMode(txt);
                    txt->insert_to_normal();
                }
                txt->refresh(NORMAL_MODE);
                break;
            case 'd':
                if ( getch() == 'd' ) if ( !(txt->is_read_only()) ) txt->delete_line();
                txt->refresh(NORMAL_MODE);
                break;
            case 'O':
                txt->move_to_the_beginning();
                break;
            case '$':
                txt->move_to_the_end();
                break;
            case 'w':
                txt->move_forward();
                break;
            case 'b':
                txt->move_backward();
                break;
        }

    }
}