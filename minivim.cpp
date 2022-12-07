#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "minivim.h"
using std::vector;
using std::string;

#define REG_COLOR_NUM 1
#define CUS_COLOR_NUM 2

WINDOW *txtwin, *infowin, *cmdwin;

int main( int argc, char *argv[] ){
    initscr(); /* Start curses mode */
    raw();
    noecho();
    keypad(stdscr, true); /*stdscr is the regular window*/
    // init color
    start_color();
    init_pair(REG_COLOR_NUM, COLOR_WHITE, COLOR_BLACK);
    init_pair(CUS_COLOR_NUM, COLOR_WHITE, COLOR_BLUE);
    // set stdscr color
    wbkgd(stdscr, COLOR_PAIR(REG_COLOR_NUM));
    wrefresh(stdscr);
    
    // create and init the windows
    txtwin = newwin(win_row, win_col, 0, 0);
    infowin = newwin(1, COLS, win_row, 0);
    cmdwin = newwin(1, COLS, win_row + 1, 0);
    keypad(txtwin, true);
    wbkgd(txtwin, COLOR_PAIR(CUS_COLOR_NUM)); /*set customized window color*/
    wrefresh(txtwin);

    textfile *txt = argc > 1 ? new textfile(argv[argc - 1]) : new textfile();
    NormalMode(txt);

    // End curses mode
    endwin();
    return 0;
}