/*
 * Oaksouls Testing Suite ~ curses functionality test.
 * Copyright (C) 2018  Eli Stone eli.stonium+oak@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <curses.h>


#define RETURNVALUE 0
#ifndef CURSES
#undef RETURNVALUE
#define RETURNVALUE 255
#endif


int main() {
    
    int i = RETURNVALUE;
    if (i != 0) {
        std::cout << "Ncurses not loaded for some reason" << std::endl;
        return i;
    }
    
    initscr();
    cbreak();
    noecho();
    //int errcode = start_color();

    
    if (! has_colors()) {
        curs_set(1);
        clear();
        endwin();
        std::cout << "Terminal does not support color. Test failed." << std::endl;
        return 1;
    } else {
        std::cout << "Test 1 passed, terminal has colors" << std::endl;
    }
    
    if (! can_change_color()) {
        curs_set(1);
        clear();
        endwin();
        std::cout << "Terminal does not support color changing. Test failed." << std::endl;
        return 1;
    } else {
        start_color();
        init_color(120, 900, 900, 0);
        init_color(130, 0, 0, 500);
        init_pair(19, 120, 130);
        attron(COLOR_PAIR(19));
        printw("Test 2 passed, terminal has color changing\n");
        
        
        getch();
    }
    
    curs_set(1);
    clear();
    endwin();
    short colnum = tigetnum("colors");
    std::cout << "Number of colors supported by terminal: " << colnum << std::endl;
    return i;
}
