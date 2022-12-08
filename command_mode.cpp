#include <ncurses.h>
#include <vector>
#include <string>
#include <sstream>
#include "minivim.h"

extern WINDOW *txtwin, *infowin, *cmdwin;


int CommandMode( textfile *txt ){
    static vector<string> h_cmd;
    
    wclear(cmdwin);
    wprintw(cmdwin, ":");
    wrefresh(cmdwin);
    
    vector<string> cmd = h_cmd;
    cmd.push_back("");
    string c1, c2, c3;
    
    int ch, x = 0, y = (int)cmd.size() - 1;
    while( (ch = getch()) != 10 ){
        switch( ch ){
            case 27:
                wclear(cmdwin);
                wrefresh(cmdwin);
                return 0;
                break;
            case KEY_LEFT:
                if ( x > 0 ) --x;
                break;
            case KEY_RIGHT:
                if ( x + 1 < cmd[y].size() ) ++x;
                break;
            case KEY_UP:
                if ( y > 0 ){
                    --y;
                    x = cmd[y].size();
                }
                break;
            case KEY_DOWN:
                if ( y + 1 < cmd.size() ){
                    ++y;
                    x = cmd[y].size();
                }
                break;
            case KEY_BACKSPACE:
                if ( x > 0 ){
                    if ( x == cmd[y].size() ) cmd[y].pop_back();
                    else cmd[y] = cmd[y].substr(0, x - 1) + cmd[y].substr(x + 1);
                    --x;
                }
                break;
            default:
                if ( x == cmd[y].size() ) cmd[y].push_back((char)ch);
                else cmd[y] = cmd[y].substr(0, x) + (char)ch + cmd[y].substr(x + 1);
                ++x;
                break;
        }
        wclear(cmdwin);
        wprintw(cmdwin, ":%s", cmd[y].c_str());
        wmove(cmdwin, 0, x + 1);
        wrefresh(cmdwin);
    }
    wclear(cmdwin);
    wrefresh(cmdwin);

    h_cmd.push_back(cmd[y]);
    std::istringstream iss(cmd[y]);
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