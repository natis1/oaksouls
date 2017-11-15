/*
 * This displays the map... somehow
 * Copyright (C) 2017  <copyright holder> <email>
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
#include <vector>
#include <unistd.h>
#include "display_manager.h"

//debug only
#include <iostream>


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
            usleep(10000);
        } else if ( c == 'q' ) {
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


int display_manager::FBLogLoop(int startingValue)
{
    move(0,0);
    printw("Message history - Press q to return to the game.");
    int height = getmaxy(stdscr);
    move(0,1);
    for (int i = startingValue; i < FBHistory.size(); i++) {
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
            printw(FBHistory.at(i).c_str());
            printw("\n");
        }
    }
    return FBHistory.size();
}


void display_manager::drawIntro()
{
    move(1,0);
    int y = 1;
    printw("In a field of grass lies a single oak tree.\n");
    printw("It sits protected in its little world from the monsters around it.\n");
    printw("Until one day, when it finally grows big enough to take on the world.\n\n");
    printw("You control this oak...");
    getch();
    move(0,0);
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    
    
    
    nodelay(stdscr, TRUE);
    int c = 0;
    move(0,0);
    do {
        usleep(10000);
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
    nodelay(stdscr, FALSE);
    drawMainMenu();
}

int display_manager::drawMainMenu()
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
    int action = 0;
    while (action == 0) {
        switch (getch()) {
            case 'n':
                action = 1;
            case 'l':
                action = 2;
            case 'o':
                action = 3;
            case 's':
                action = 4;
            case 't':
                action = 5;
            case 'q':
                action = 6;
        }
    }
    return action;
}


