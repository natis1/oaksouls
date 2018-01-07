/*
 * Oaksouls ~ A difficult roguelike about a	tree spirit.
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
#include <ncurses.h>
#include "display_manager.h"
#include <signal.h>
#include <execinfo.h>

void signal_cleanup(int sig) {
    std::cerr << "Recieved signal: " << sig << std::endl;
    
    void *buffer[300];
    int j, k;
    k = backtrace(buffer, 300);
    char **strings = backtrace_symbols(buffer, k);
    for (j = 0; j < k; j++) {
        std::cerr << strings[j] << std::endl;
    }
    
    curs_set(1);
    clear();
    endwin();
    exit(sig);
}

void ctrl_c_cleanup(int sig) {
    clear();
    curs_set(1);
    //TODO: Implement saving right here
    endwin();
    
    std::cout << "Ctrl+c hit. Saving and exiting" << std::endl;
    exit(sig);
    
    
}

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    display_manager display;
    if (display.initDisplay() == -1 ) {
        std::cerr << "Unable to start 256-bit color." << std::endl;
        std::cerr << "Try upgrading to an operating system younger than you" << std::endl;
        std::cerr << "Or switching to a terminal or terminal emulator that isn't shit." << std::endl;
        return -1;
    }
    // Recover from intentional killing and also segfaults in case I messed up my code
    signal(SIGINT,ctrl_c_cleanup);
    signal(SIGKILL,signal_cleanup);
    signal(SIGSEGV,signal_cleanup);
    
    int result = display.drawIntro();
    std::string savefile;
    if (result == 1) {
        //code to start and then save a new game
        savefile = "oak.dat";
    } else if (result == 6) {
        display.cleanDisplay();
        return 0;
    }
    // code to load a saved game
    
    
    
    display.cleanDisplay();
    return 0;
}


