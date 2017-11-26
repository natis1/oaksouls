/*
 * Decides what information to send to the terminal
 * Copyright (C) 2017  Eli Stone
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

#pragma once

//Hell yeah
#include <ncurses.h>

#include <vector>

#include "level.h"
#include "monster.h"
#include "performance.h"

class display_manager
{
public:
    void drawBaseLayer();
    void drawMonsterLayer();
    void drawFrameBuffer();
    void drawStatsLayer();
    
    void drawFBLog();
    
    int drawIntro();
    void drawMainMenu();
    int mainMenuLoop();
    
    int initDisplay();
    void cleanDisplay();
    
private:
    // A complete log of the framebuffer.
    char [50] [161] FBHistory;
    int FBLogLoop(int startingValue);
    
    void menuPlantTree();
    void menuShowStats();
    void menuOptions();
    
    void highlightLine(int y);
};
