/*
 * Oaksouls ~ A difficult roguelike about a tree spirit.
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
#include "color.h"
#include "string.h"
#include "global_define.h"



void signal_cleanup(int sig) {
    curs_set(1);
    clear();
    endwin();
    
    std::cerr << "Recieved signal: " << sig << std::endl;
    if (sig == SIGSEGV) {
        std::cerr << "Segmentation Fault!" << std::endl;
    }
    
    if (sig == SIGABRT) {
        std::cerr << "Aborted!" << std::endl;
    }
    
    void *buffer[300];
    int j, k;
    k = backtrace(buffer, 300);
    char **strings = backtrace_symbols(buffer, k);
    for (j = 0; j < k; j++) {
        std::cerr << strings[j] << std::endl;
    }
    
    
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

void init_globals() {
    
    bool fullc = false;
    char * terminalUsed = getenv("TERM");
    if (strcmp(terminalUsed, "xterm-256color") == 0) {
        fullc = true; // So help me god never set this again
    } else {
        //init_color(120, 900, 900, 0);
        //init_color(130, 0, 0, 500);
        init_pair(65, COLOR_GREEN, COLOR_BLACK);
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        move(11,0);
        attron(COLOR_PAIR(65));
        printw("If you can see this text, your terminal (might be) lying to you!\nIt might draw more colors than it claims\npress c to enable full color mode\nif it works add export TERM=xterm-256color to ~/.bashrc to keep it.\nTerminal is emulating: ");
        printw(terminalUsed);
        attron(COLOR_PAIR(1));
    }
    move(1,0);
    printw("In a field of grass lies a single oak tree.\n");
    printw("It sits protected in its little world from the monsters around it.\n");
    printw("Until one day, when it finally grows big enough to take on the world.\n\n");
    printw("You control this oak...");
    char inp = getch();
    if ( inp == 'c' ) {
        
        if (setenv("TERM", "xterm-256color", 1) != 0) {
            move(0,0);
            printw("Unable to set environment variable to enable full color support");
            getch();
        } else {
            fullc = true;
        }
        move(0,0);
    }
    USE_FULL_COLOR = fullc;
    
    if (USE_FULL_COLOR) {
        BRIGHT_WHITE = 65;
        BRIGHT_BLACK = 66;
        BRIGHT_RED = 67;
        BRIGHT_YELLOW = 68;
        BRIGHT_GREEN = 69;
        BRIGHT_CYAN = 70;
        BRIGHT_BLUE = 71;
        BRIGHT_MAGENTA = 72;

        VIVID_WHITE = 73;
        VIVID_BLACK = 74;
        VIVID_RED = 75;
        VIVID_YELLOW = 76;
        VIVID_GREEN = 77;
        VIVID_CYAN = 78;
        VIVID_BLUE = 79;
        VIVID_MAGENTA = 80;

        NORMAL_WHITE = 81;
        NORMAL_BLACK = 82;
        NORMAL_RED = 83;
        NORMAL_YELLOW = 84;
        NORMAL_GREEN = 85;
        NORMAL_CYAN = 86;
        NORMAL_BLUE = 87;
        NORMAL_MAGENTA = 88;

        DARK_WHITE = 89;
        DARK_BLACK = 90;
        DARK_RED = 91;
        DARK_YELLOW = 92;
        DARK_GREEN = 93;
        DARK_CYAN = 94;
        DARK_BLUE = 95;
        DARK_MAGENTA = 96;
        
    } else {
        BRIGHT_WHITE = COLOR_WHITE;
        BRIGHT_BLACK = COLOR_BLACK;
        BRIGHT_RED = COLOR_RED;
        BRIGHT_YELLOW = COLOR_YELLOW;
        BRIGHT_GREEN = COLOR_GREEN;
        BRIGHT_CYAN = COLOR_CYAN;
        BRIGHT_BLUE = COLOR_BLUE;
        BRIGHT_MAGENTA = COLOR_MAGENTA;

        VIVID_WHITE = COLOR_WHITE;
        VIVID_BLACK = COLOR_BLACK;
        VIVID_RED = COLOR_RED;
        VIVID_YELLOW = COLOR_YELLOW;
        VIVID_GREEN = COLOR_GREEN;
        VIVID_CYAN = COLOR_CYAN;
        VIVID_BLUE = COLOR_BLUE;
        VIVID_MAGENTA = COLOR_MAGENTA;

        NORMAL_WHITE = COLOR_WHITE;
        NORMAL_BLACK = COLOR_BLACK;
        NORMAL_RED = COLOR_RED;
        NORMAL_YELLOW = COLOR_YELLOW;
        NORMAL_GREEN = COLOR_GREEN;
        NORMAL_CYAN = COLOR_CYAN;
        NORMAL_BLUE = COLOR_BLUE;
        NORMAL_MAGENTA = COLOR_MAGENTA;

        DARK_WHITE = COLOR_WHITE;
        DARK_BLACK = COLOR_BLACK;
        DARK_RED = COLOR_RED;
        DARK_YELLOW = COLOR_YELLOW;
        DARK_GREEN = COLOR_GREEN;
        DARK_CYAN = COLOR_CYAN;
        DARK_BLUE = COLOR_BLUE;
        DARK_MAGENTA = COLOR_MAGENTA;
    }
    
}

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    display_manager display;
    if (display.initDisplay() == -1 ) {
        std::cerr << "Unable to start display." << std::endl;
        std::cerr << "Try upgrading to an operating system younger than you" << std::endl;
        std::cerr << "Or switching to a terminal or terminal emulator that isn't shit." << std::endl;
        return -1;
    }
    // Recover from intentional killing and also segfaults in case I messed up my code
    signal(SIGINT,ctrl_c_cleanup);
    signal(SIGKILL,signal_cleanup);
    signal(SIGABRT,signal_cleanup);
    signal(SIGSEGV,signal_cleanup);
    
    init_globals();
    int result = display.drawIntro();
    std::string savefile;
    if (result == 1) {
        //code to start and then save a new game
        savefile = "oak.dat";
        while (true) {
            level(1, 1);
            
        }
        std::cerr << "Can anyone hear me?" << std::endl;
        getch();
        
    } else if (result == 6) {
        display.cleanDisplay();
        return 0;
    }
    // code to load a saved game
    
    
    
    display.cleanDisplay();
    return 0;
}


