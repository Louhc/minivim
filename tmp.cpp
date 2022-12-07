if ( x > 0 ){
    --x;
    wclear(win_info);
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, min(y, (int)text[x].size() - 1));
    wrefresh(win_info);
    node t(nCalcPos(x, y)); int tmp = nCalcPos(x, 0).x;
    if ( tmp < ul ){
        for ( int i = ul - tmp - 1; i >= 0; --i ){
            --ul; wmove(win_txt, 0, 0); winsertln(win_txt);
            wprintw(win_txt, "%s", text[x].substr(i * COLS, min(COLS, (int)text[x].size() - i * COLS)).c_str());
        }
    }
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}

if ( x + 1 < text.size() ){
    ++x;
    wclear(win_info);
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, min(y, (int)text[x].size() - 1));
    wrefresh(win_info);
    node t(nCalcPos(x, y)); int tmp = nCalcPos(x, (int)text[x].size() - 1).x;
    if ( tmp - ul > LINES - 3 ){
        for ( int i = ((int)text[x].size() - 1) / COLS - (tmp - ul + 2 - LINES); i <= ((int)text[x].size() - 1) / COLS; ++i ){
            ++ul; wmove(win_txt, 0, 0); wdeleteln(win_txt); wmove(win_txt, LINES - 3, 0);
            wprintw(win_txt, "%s", text[x].substr(i * COLS, min(COLS, (int)text[x].size() - i * COLS)).c_str());
        }
    }
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}

y = min(y, (int)text[x].size() - 1);
if ( y > 0 ){
    --y;
    wclear(win_info);
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, y);
    wrefresh(win_info);
    node t(nCalcPos(x, y));
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}

y = min(y, (int)text[x].size() - 1);
if ( y + 1 < text[x].size()){
    ++y;
    node t(nCalcPos(x, y));
    wclear(win_info);
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, y);
    wrefresh(win_info);
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}







if ( x > 0 ){
    --x;
    wclear(win_info);
    wprintw(win_info, "-- INSERT --");
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, min(y, (int)text[x].size()));
    wrefresh(win_info);
    node t(iCalcPos(x, y)); int tmp = iCalcPos(x, 0).x;
    if ( tmp < ul ){
        for ( int i = ul - tmp - 1; i >= 0; --i ){
            --ul; wmove(win_txt, 0, 0); winsertln(win_txt);
            wprintw(win_txt, "%s", text[x].substr(i * COLS, min(COLS, (int)text[x].size() - i * COLS)).c_str());
        }
    }
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}

if ( x + 1 < text.size() ){
    ++x;
    wclear(win_info);
    wprintw(win_info, "-- INSERT --");
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, min(y, (int)text[x].size()));
    wrefresh(win_info);
    node t(iCalcPos(x, y)); int tmp = iCalcPos(x, (int)text[x].size() - 1).x;
    if ( tmp - ul > LINES - 3 ){
        for ( int i = ((int)text[x].size() - 1) / COLS - (tmp - ul + 2 - LINES); i <= ((int)text[x].size() - 1) / COLS; ++i ){
            ++ul; wmove(win_txt, 0, 0); wdeleteln(win_txt); wmove(win_txt, LINES - 3, 0);
            wprintw(win_txt, "%s", text[x].substr(i * COLS, min(COLS, (int)text[x].size() - i * COLS)).c_str());
        }
    }
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}

y = min(y, (int)text[x].size());
if ( y > 0 ){
    --y;

    wclear(win_info);
    wprintw(win_info, "-- INSERT --");
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, y);
    wrefresh(win_info);
    
    node t(iCalcPos(x, y));
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}

y = min(y, (int)text[x].size());
if ( y + 1 <= text[x].size()){
    ++y;
    
    wclear(win_info);
    wprintw(win_info, "-- INSERT --");
    wmove(win_info, 0, COLS - 17);
    wprintw(win_info, "%d,%d", x, y);
    wrefresh(win_info);
    
    node t(iCalcPos(x, y));
    wmove(win_txt, t.x - ul, t.y);
    wrefresh(win_txt);
}




y = min(y, (int)text[x].size());
if ( y == 0 ){
    if ( x == 0 ) break;
    ul = min(ul, iCalcPos(x - 1, 0).x);
    y = text[x - 1].size();
    text[x - 1] += text[x];
    for ( int i = x; i < (int)text.size() - 1; ++i )
        text[i] = text[i + 1];
    text.pop_back(); --x;
} else {
    if ( y == text[x].size() ) text[x] = text[x].substr(0, (int)text[x].size() - 1), --y;
    else text[x] = text[x].substr(0, y - 1) + text[x].substr(y, (int)text[x].size() - y), --y;
}
RefreshText();


y = min(y, (int)text[x].size());
text.push_back("");
for ( int i = (int)text.size() - 2; i >= x + 1; --i )
    text[i + 1] = text[i];
if ( y == text[x].size() ) text[x + 1] = "";
else text[x + 1] = text[x].substr(y, (int)text.size() - y), text[x] = text[x].substr(0, y);
++x; y = 0;
ul = max(ul, iCalcPos(x, (int)text[x].size() - 1).x + 3 - LINES);
RefreshText();


y = min(y, (int)text[x].size());
if ( y == text[x].size() ) text[x] = text[x].substr(0, y) + (char)ch;
else text[x] = text[x].substr(0, y) + (char)ch + text[x].substr(y, text[x].size() - y);
++y;
ul = max(ul, iCalcPos(x, (int)text[x].size() - 1).x + 3 - LINES);
RefreshText();