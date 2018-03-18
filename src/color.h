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

#pragma once
#include <curses.h>


#define BRIGHT_ALGO linearBrightness

// Backgrounds must be neutral (grey before tint)
#define FORCE_NEUTRAL_BACKGROUNDS true

// The difference between the background and active color is multiplied by this for more extreme colors and more toned down backgrounds.s
#define SATURATION 1.0

// C1 = C0 ^ Gamma
#define GAMMA 1.0

/*
 * The color palette consists of four sets of 8 colors.
 * These four sets represent four different brightness levels (sorta).
 * 
 * Bright colors are as bright as possible without clipping. At brightness = 1, this means
 * primary colors have brighnesses of 1 of their respective color. Secondary ones have brighnesses of 1 / (sqrt 2).
 * And backgrounds are half brightness: 1/( 2 sqrt(3) ).
 * 
 * This is because actual brighness of any given pixel is the square of its brightness value. So r = 1/sqrt(2), g = 1/sqrt(2), b = 0
 * will look just as bright as r = 1, g = 0, b = 0.
 * 
 * Vivid colors are the same as bright colors except their background brightness is 0.
 * Dungeon features no longer in sight range, and some enemies are vivid.
 * 
 * Normal colors have a background brightness of 0 and a normal brightness of 1/2.
 * These apply to stuff that's not currently visible, enemy attacks, etc.
 * 
 * Dark colors have a background brightness of 0 and a normal brightness of 1/4.
 * These rarely apply when certain status effects are present.
 * 
 * 
 */

#define BRIGHT_BG 60
#define NORMAL_BG 61
// etc for other colors

extern bool USE_FULL_COLOR;
extern short BRIGHT_WHITE;
extern short BRIGHT_BLACK;
extern short BRIGHT_RED;
extern short BRIGHT_YELLOW;
extern short BRIGHT_GREEN;
extern short BRIGHT_CYAN;
extern short BRIGHT_BLUE;
extern short BRIGHT_MAGENTA;

extern short VIVID_WHITE;
extern short VIVID_BLACK;
extern short VIVID_RED;
extern short VIVID_YELLOW;
extern short VIVID_GREEN;
extern short VIVID_CYAN;
extern short VIVID_BLUE;
extern short VIVID_MAGENTA;

extern short NORMAL_WHITE;
extern short NORMAL_BLACK;
extern short NORMAL_RED;
extern short NORMAL_YELLOW;
extern short NORMAL_GREEN;
extern short NORMAL_CYAN;
extern short NORMAL_BLUE;
extern short NORMAL_MAGENTA;

extern short DARK_WHITE;
extern short DARK_BLACK;
extern short DARK_RED;
extern short DARK_YELLOW;
extern short DARK_GREEN;
extern short DARK_CYAN;
extern short DARK_BLUE;
extern short DARK_MAGENTA;

/**
 * @todo write docs
 */
class color
{
public:
    void setBrightness(double bright);
    void setTint(double r, double g, double b);
    
    void reloadColors();
    
    // This may only need to be done once, it might be needed to do it a lot of times. Not sure yet.
    void initColors();
protected:
    bool needsReload = false;
    
    // Scale from 0 - 1 how bright is it?
    double brightness = 1;
    
    // Filters to apply
    double redTint = 2;
    double greenTint = 2;
    double blueTint = 2;
    
    
    
private:

    void setBlandColorArray();
    
    void setColor(short index, double bright, double redMod, double greenMod, double blueMod);
    void setPairs();
    void clipColors();
    
    
    
    
};
