#include <iostream>
#include <ncurses.h>
#include "display_manager.h"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    initscr();
    cbreak();
    noecho();
    start_color();
    
    display_manager display;
    display.drawIntro();
    
    curs_set(1);
    clear();
    endwin();
    refresh();
    
    return 0;
}
