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
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include "display_manager.h"
#include "file_manager.h"
#include <string.h>

#include "color.h"
#include <stdlib.h>


//debug only
#include <iostream>


int display_manager::initDisplay()
{
    initscr();
    cbreak();
    noecho();
    int errcode = start_color();
    return errcode;
}

void display_manager::cleanDisplay()
{
    curs_set(1);
    clear();
    endwin();    
}

/*
void display_manager::drawFBLog()
{
    if ( FBHistory.size() < 1 ) {
        FBHistory.push_back("You have no new messages. Go out and explore the world!");
    }
    bool quit = false;
    int mStart = 0;
    int mEnd;
    nodelay(stdscr, TRUE);
    do {
        int c = getch();
        if ( c == 0 ) {
            usleep(SLOW_REDRAW_DELAY);
        } else if (c == 'q' ) {
            quit = true;
        } else if (c == 'z') {
            mStart = mEnd;
            mEnd = FBLogLoop(mStart);
        } else if (c == 'a') {
            mStart = mStart - (mEnd - mStart);
            mEnd = FBLogLoop(mStart);
        } else if (c == '\033') {
            if ( getch() == '[' ) {
                switch (getch()) {
                    case 'A':
                        mStart--;
                        mEnd = FBLogLoop(mStart);
                        break;
                    case 'B':
                        mStart++;
                        mEnd = FBLogLoop(mStart);
                        break;
                }
                
            }
        }
        
    } while ( !quit );
    
    nodelay(stdscr, FALSE);
}
*/

int display_manager::FBLogLoop(int startingValue)
{
    move(0,0);
    printw("Message history - Press q to return to the game.");
    int height = getmaxy(stdscr);
    move(0,1);
    for (unsigned int i = startingValue; i < 50; i++) {
        int x; //discarded but whatever
        int y;
        getyx(stdscr, y, x);
        if ( y >= height ) {
            y = height;
            move(0,y);
            printw(":");
            return i;
        } else {
            move(0,y);
            printw(FBHistory[i]);
            printw("\n");
        }
    }
    return 50;
}


int display_manager::drawIntro()
{
    move(0,0);
    int xsize, ysize;
    getmaxyx(stdscr, ysize, xsize);
    if (xsize != 80 || ysize < 24) {
        nodelay(stdscr, TRUE);
        int c = 0;
        move(0,0);
        init_pair(1, COLOR_BLACK, COLOR_BLUE);
        init_pair(2, COLOR_BLACK, COLOR_GREEN);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        do {
            usleep(SLOW_REDRAW_DELAY);
            if (c != -1) {
                clear();
                printw("Please adjust the terminal until the picture perfectly fits and press space.....");
                attron(COLOR_PAIR(1));
                printw("................................................................................");
                printw("................................................................................");
                printw("................................................................................");
                printw("................................................................................");
                printw("...................................");attron(COLOR_PAIR(3)); printw("Oak Souls"); attron(COLOR_PAIR(1)); printw("....................................");
                printw("................................................................................");
                printw("................................................................................");
                printw("................................................................................");
                printw("............"); attron(COLOR_PAIR(2)); printw("/LLLLLLLLLLLLLLL"); attron(COLOR_PAIR(1)); printw("....................................................");
                printw("......."); attron(COLOR_PAIR(2)); printw("////LLLLLLLLLLLLLLLLLLL"); attron(COLOR_PAIR(1)); printw("..................................................");
                printw("......"); attron(COLOR_PAIR(2)); printw("//LLLLLLLLLLLLLLLLLLLLLLLLL"); attron(COLOR_PAIR(1)); printw("...............................................");
                printw("....."); attron(COLOR_PAIR(2)); printw("//LLLLLLLLLLLLLLLLLLLLLLLLLLLLL"); attron(COLOR_PAIR(1)); printw("............................................");
                printw("...."); attron(COLOR_PAIR(2)); printw("///LLLLLLLLLLLLLLLLLLLLLLLLLLLLL/"); attron(COLOR_PAIR(1)); printw("...........................................");
                printw("....."); attron(COLOR_PAIR(2)); printw("//LLLLLLLLLLLLLLLLLLLLLLLLLLLL//"); attron(COLOR_PAIR(1)); printw("...........................................");
                printw("....."); attron(COLOR_PAIR(2)); printw("//LLLLLLLLLLLLLTTLLLLLLLLLLL/"); attron(COLOR_PAIR(1)); printw("..............................................");
                printw("......"); attron(COLOR_PAIR(2)); printw("/LLLLLLLLLLLLTTTTLLLLLLLLLL"); attron(COLOR_PAIR(1)); printw("...............................................");
                printw("......"); attron(COLOR_PAIR(2)); printw("/LLLLLLLLLLLLTTTTLLLLLLLLL"); attron(COLOR_PAIR(1)); printw("................................................");
                printw(".................."); attron(COLOR_PAIR(2)); printw("/TTTT"); attron(COLOR_PAIR(1)); printw(".........................................................");
                printw("......"); attron(COLOR_PAIR(2)); printw("::::::::::::/TTTT::::::::::"); attron(COLOR_PAIR(1)); printw("..............................."); attron(COLOR_PAIR(2)); printw("@"); attron(COLOR_PAIR(1)); printw("...............");
                attron(COLOR_PAIR(2)); printw("###################TTTT#########################################################");
                printw("##########RRRRRRR#RRRRRR#RRRRRRR################################################");
                printw("#################R##RR##R#######################################################");
                printw("#############RRRR###RR###RRRRRR################################################\n");
                attron(COLOR_PAIR(3));
                printw("#The terminal is too large if you are seeing this line.");
                move(0,0);
            }
            c = getch();
        }
        while ( c != ' ' );
    }
    nodelay(stdscr, FALSE);
    drawMainMenu();
    return mainMenuLoop();
}


void display_manager::drawMainMenu()
{
    clear();
    move(6,35);
    printw("Oak Souls");
    int center = 29;
    move(10,center);
    printw("Start a [n]ew game");
    move(11,center);
    printw("[L]oad an existing save");
    move(12,center);
    printw("Check out the dank [o]ptions menu");
    move(13,center);
    printw("Get forest [s]tatistics");
    move(14,center);
    printw("Plant a [t]ree");
    move(15,center);
    printw("[Q]uit the game");
    
}

int display_manager::mainMenuLoop()
{
    while (true) {
        switch (getch()) {
            case 'n':
                return 1;
            case 'l':
                return 2;
            case 'o':
                menuOptions();
                break;
            case 's':
                menuShowStats();
                break;
            case 't':
                menuPlantTree();
                break;
            case 'q':
                return 6;
        }
    }
}


void display_manager::menuOptions()
{
    //load options file 
    file_manager fm;
    options opts = fm.loadOptions();
    options* optsptr= &opts;
    
    std::vector<std::string> lines;

    
    //TODO: Figure out how to make a char* out of you. Or maybe just a vector, idc.
    
    optsptr->checkOptions();
    getch();
    drawMainMenu();
}

void display_manager::menuShowStats()
{
    //load stats file
    
    file_manager fm;
    statistics stat = fm.loadStatistics();
    statistics* stats = &stat;
    std::cerr << "stats loaded" << std::endl;

    
    std::cerr << stats->forestName << stats->forestXP << stats->getForestArea() << " are some stats" << std::endl;
    clear();
    move(2,0);
    std::ostringstream osline;
    
    osline << "Best Forest: " << stats->forestName << std::endl;
    osline << "XP:" << stats->forestXP << "    Souls:" << stats->forestCreatures << std::endl;
    osline << "Runs:" << stats->forestGamesPlayed << "    Deaths:" << stats->forestDeaths << "    Floors:" << stats->forestFloors << std::endl;
    osline << "Area:" << stats->getForestArea() << std::endl;
    osline << std::endl << std::endl;
    
    osline << "Best Hero: " << stats->highestName << std::endl;
    osline << "XP:" << stats->highestXP << "    Souls:" << stats->highestCreatures << std::endl;
    osline << "Level:" << stats->highestLevel << "    Floors:" << stats->highestFloors << std::endl;
    osline << std::endl << std::endl;
    
    osline << "Total Stats" << std::endl;
    osline << "XP:" << stats->totalXP << "    Souls:" << stats->totalCreatures << std::endl;
    osline << "Runs:" << stats->totalGamesPlayed << "    Deaths:" << stats->totalDeaths << "    Floors:" << stats->totalFloors << std::endl;
    std::string s = osline.str();
    
    char* c = new char[s.length() + 1];
    strcpy(c,s.c_str());
    printw(c);
    printw("\n\nPress any key to return to the main menu");
    getch();
    drawMainMenu();
}

void display_manager::menuPlantTree()
{
    clear();
    move(0,0);
    printw("If you have a backyard, you may be able to plant your very own tree or bush.");
    move(2,0);
    attron(COLOR_PAIR(2));
    printw("Advantages");
    move(3,0);
    attron(COLOR_PAIR(3));
    printw("Large plants can look cool, fight pests, and provide shade");
    move(4,0);
    printw("Plus, they are way better for the environment than grass");
    
    move(6,0);
    printw("If you are interested in learning more, check out:");
    move(7,0);
    printw("man 7 oaksouls");
    
    move(20,0);
    printw("Good luck!");
    move(22,0);
    printw("Press any key to return to the main menu.");
    getch();
    drawMainMenu();
}

void display_manager::highlightLine(int y)
{
    
    
    
}





