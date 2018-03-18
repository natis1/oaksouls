/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  <copyright holder> <email>
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

#include "color.h"
#include <math.h>

#include <iostream>

void color::initColors()
{
    setBrightness(1.0);
    setTint(1.0, 1.0, 1.0);
    start_color();
    
    if (USE_FULL_COLOR) {
        reloadColors();
        setPairs();
    } else {
        setBlandColorArray();
    }
    
}


void color::setBrightness(double bright)
{
    if (brightness != bright) {
        brightness = bright;
        needsReload = true;
    }
}

void color::setTint(double r, double g, double b)
{
    if (redTint != r || greenTint != g || blueTint != b) {
        redTint = r;
        greenTint = g;
        blueTint = b;
        needsReload = true;
    }
}


void color::reloadColors()
{
    setColor(BRIGHT_BG, pow(brightness / 2.0, ( 1.0 / GAMMA)), 1., 1., 1.);
    setColor(NORMAL_BG, 0, 1., 1., 1.);
    setColor(NORMAL_BG + 1, 0, 1., 1., 1.);
    setColor(NORMAL_BG + 2, 0, 1., 1., 1.);    
    //setColor(BBLACK_FG, 0, 1., 1., 1.);
    
    for (int i = 0; i < 3; i++) {
        double brightActual = brightness / (pow(1.5, (i - 1) ) );
        setColor(BRIGHT_WHITE + (7 * i), brightActual, 1., 1., 1. );
        setColor(BRIGHT_WHITE + (7 * i) + 1, brightActual, 1., 0, 0 );
        setColor(BRIGHT_WHITE + (7 * i) + 2, brightActual, 1., 1., 0);
        setColor(BRIGHT_WHITE + (7 * i) + 3, brightActual, 0, 1., 0);
        setColor(BRIGHT_WHITE + (7 * i) + 4, brightActual, 0, 1., 1. );
        setColor(BRIGHT_WHITE + (7 * i) + 5, brightActual, 0, 0, 1. );
        setColor(BRIGHT_WHITE + (7 * i) + 6, brightActual, 1., 0, 1. );
    }
    
    
    
}

void color::setColor(short index, double bright, double redMod, double greenMod, double blueMod)
{
    /*
     * So basically to explain:
     * given that
     * brightness = sqrt ( r^2 + g^2 + b^2)
     * we want to find values of r, g, b that are proportional to redMod, greenMod, and blueMod
     * 
     * Thus we get brightness = sqrt ( (alpha * redMod)^2 + (alpha * greenMod)^2 + (alpha * blueMod)^2)
     * Pull out the sqrt(alpha^2) (since brightness must be positive) to get
     * 
     * brightness = alpha sqrt( redMod^2 + greenMod^2 + blueMod ^ 2 )
     * 
     * Solve for alpha. Since alpha * redMod = r, etc. you can then solve for r.
     * 
     */
    double alpha = bright / ( sqrt(pow(redMod, 2) + pow(greenMod, 2) + pow(blueMod, 2) ) );
    double redD, greenD, blueD;
    
    redD = alpha * redMod;
    greenD = alpha * greenMod;
    blueD = alpha * blueMod;
    short r, g, b;
    r = redD * 1000;
    g = greenD * 1000;
    b = blueD * 1000;
    
    // Clip colors to stop overflow
    
    //TODO: clip all colors by the same percentageif any one clips.
    
    if (r > 1000) {
        r = 1000;
    } else if (r < 0) {
        r = 0;
    }
    
    if (g > 1000) {
        g = 1000;
    } else if (g < 0) {
        g = 0;
    }
    
    if (b > 1000) {
        b = 1000;
    } else if (b < 0) {
        b = 0;
    }
    
    if (init_color(index, r, g, b) != 0) {
        
        curs_set(1);
        clear();
        endwin();
        std::cerr << "Unable to init color of index " << index << std::endl;
        std::cerr << "Number of valid colors/ color pairs: " << COLORS << "/" << COLOR_PAIRS << std::endl;
        exit(11);
    }
    
}


void color::setPairs()
{
    // This is awful
    // Take a look at this hacky shit. Hope it works right because this will suck to debug
    for (int i = 0; i < 3; i++) {
        init_pair(BRIGHT_WHITE + (8 * i)    , BRIGHT_WHITE + (7 * i)    , BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 1, NORMAL_BG                 , BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 2, BRIGHT_WHITE + (7 * i) + 1, BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 3, BRIGHT_WHITE + (7 * i) + 2, BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 4, BRIGHT_WHITE + (7 * i) + 3, BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 5, BRIGHT_WHITE + (7 * i) + 4, BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 6, BRIGHT_WHITE + (7 * i) + 5, BRIGHT_BG + i);
        init_pair(BRIGHT_WHITE + (8 * i) + 7, BRIGHT_WHITE + (7 * i) + 6, BRIGHT_BG + i);
        
    }
    
}


void color::setBlandColorArray()
{
    // Enjoy your EGA for using a bad terminal emulator
    init_pair(BRIGHT_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(BRIGHT_BLACK, COLOR_BLACK, COLOR_WHITE);
    init_pair(BRIGHT_RED, COLOR_RED, COLOR_BLACK);
    init_pair(BRIGHT_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BRIGHT_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(BRIGHT_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(BRIGHT_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(BRIGHT_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}


