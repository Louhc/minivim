#include <ncurses.h>
#include "minivim.h"

void InsertMode( textfile *txt ){
    int ch;
    txt->refresh(INSERT_MODE);
    while( (ch = getch()) != 27 ){
        switch( ch ){
            case KEY_UP:
                txt->go_up(INSERT_MODE);
                break;
            case KEY_DOWN:
                txt->go_down(INSERT_MODE);
                break;
            case KEY_LEFT:
                txt->go_left(INSERT_MODE);
                break;
            case KEY_RIGHT:
                txt->go_right(INSERT_MODE);
                break;
            case KEY_BACKSPACE:
                txt->backspace();
                break;
            case 10: // Enter
                txt->enter();
                break;
            default:
                if ( ch == '\t' ) for ( int i = 0; i < TAB_WIDTH; ++i ) txt->insert(' ');
                else txt->insert(ch);
                break;
        }
    }
}