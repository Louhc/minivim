#include <ncurses.h>
#include <vector>
#include <string>
#include "minivim.h"

extern WINDOW *txtwin, *infowin, *cmdwin;

int CommandMode( textfile *txt ){
    wclear(cmdwin);
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
        txt->save("");
        getch();
        return 0;
    } else if ( cmd == "q" ){
        if ( !txt->is_changed() ) return 1;
        wclear(infowin);
        wprintw(infowin, "File not saved (add ! to override)");
        wrefresh(infowin);
        getch();
        return 0;
    } else if ( cmd == "q!" ){
        return 1;
    } else if ( cmd == "wq" ){
        if ( txt->save("") ) return 1;
        getch();
        return 0;
    } else {
        return 0;
    }
    return 0;
}