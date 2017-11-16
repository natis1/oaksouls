#include <iostream>
#include <ncurses.h>
#include "display_manager.h"

void ncurses_clean() {
    
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


