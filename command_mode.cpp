#include <ncurses.h>
#include <vector>
#include <string>
#include "minivim.h"

extern WINDOW *txtwin, *infowin, *cmdwin;

int CommandMode( textfile *txt ){
    wprintw(cmdwin, ":");
    wrefresh(cmdwin);
    std::string cmd;
    int ch;
    while( (ch = getch()) != 10 ){
        if ( ch == 27 ){
            wdeleteln(cmdwin);
            wrefresh(cmdwin);
            return 0;
        }
        cmd += (char)ch;
        wprintw(cmdwin, "%c", ch);
        wrefresh(cmdwin);
    }
    wclear(cmdwin);
    wrefresh(cmdwin);
    if ( cmd == "w" ){
        return 1;
    } else if ( cmd == "q" ){
        return 1;
    } else if ( cmd == "q!" ){
        return 1;
    } else if ( cmd == "wq" ){
        return 1;
    } else {
        return 1;
    }
    return 0;
}