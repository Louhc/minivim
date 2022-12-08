#include <ncurses.h>
#include <vector>
#include <string>
#include <sstream>
#include "minivim.h"

extern WINDOW *txtwin, *infowin, *cmdwin;

int CommandMode( textfile *txt ){
    wclear(cmdwin);
    wprintw(cmdwin, ":");
    wrefresh(cmdwin);
    std::string cmd, c1, c2, c3;
    int ch;
    while( (ch = getch()) != 10 ){
        if ( ch == 27 ){
            wclear(cmdwin);
            wrefresh(cmdwin);
            return 0;
        }
        cmd += (char)ch;
        wprintw(cmdwin, "%c", ch);
        wrefresh(cmdwin);
    }
    wclear(cmdwin);
    wrefresh(cmdwin);

    std::istringstream iss(cmd);
    iss >> c1;

    if ( c1 == "w" ){
        if ( !(iss >> c2) ) c2 = "";
        txt->save(c2);
        getch();
        return 0;
    } else if ( c1 == "q" ){
        if ( !txt->is_changed() ) return 1;
        wclear(infowin);
        wprintw(infowin, "File not saved (add ! to override)");
        wrefresh(infowin);
        getch();
        return 0;
    } else if ( c1 == "q!" ){
        return 1;
    } else if ( c1 == "wq" ){
        if ( !(iss >> c2) ) c2 = "";
        if ( txt->save(c2) ) return 1;
        getch();
        return 0;
    } else if ( c1 == "sub" ) {
        iss >> c2; iss >> c3;
        if ( c2.size() <= 2 || c3.size() < 2 || c2[0] != '\"' || c2[(int)c2.size() - 1] != '\"' || c3[0] != '\"' || c3[(int)c3.size() - 1] != '\"' ){
            wclear(infowin);
            wprintw(infowin, "Format error");
            wrefresh(infowin);
            getch();
            return 0;
        }
        txt->replace(c2.substr(1, c2.size() - 2), c3.substr(1, c3.size() - 2));
        return 0;
    } else if (c1 == "jmp" ){
        iss >> c2;
        bool is_number = 1;
        for ( auto ch : c2 ) if ( ch > '9' || ch < '0' ){
            is_number = 0; break;
        }
        int ln = 0;
        if ( is_number ) for ( auto ch : c2 ) ln = ln * 10 + (ch & 15);
        
        if ( ln == 0 ){
            wclear(infowin);
            wprintw(infowin, "Format error");
            wrefresh(infowin);
            getch();
            return 0;
        }
        txt->jump(ln);
        return 0;
    }
    else {
        wclear(infowin);
        wprintw(infowin, "Format error");
        wrefresh(infowin);
        getch();
        return 0;
    }
    return 0;
}