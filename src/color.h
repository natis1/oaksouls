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
#define BRIGHT_WHITE 65
#define BRIGHT_BLACK 66
#define BRIGHT_RED 67
#define BRIGHT_YELLOW 68
#define BRIGHT_GREEN 69
#define BRIGHT_CYAN 70
#define BRIGHT_BLUE 71
#define BRIGHT_MAGENTA 72

#define VIVID_WHITE 73
#define VIVID_BLACK 74
#define VIVID_RED 75
#define VIVID_YELLOW 76
#define VIVID_GREEN 77
#define VIVID_CYAN 78
#define VIVID_BLUE 79
#define VIVID_MAGENTA 80

#define NORMAL_WHITE 81
#define NORMAL_BLACK 74
#define NORMAL_RED 82
#define NORMAL_YELLOW 83
#define NORMAL_GREEN 84
#define NORMAL_CYAN 85
#define NORMAL_BLUE 86
#define NORMAL_MAGENTA 87

#define DARK_WHITE 88
#define DARK_BLACK 74
#define DARK_RED 89
#define DARK_YELLOW 90
#define DARK_GREEN 91
#define DARK_CYAN 92
#define DARK_BLUE 93
#define DARK_MAGENTA 94



#define BRIGHT_BG 64
#define NORMAL_BG 65

// Color definitions
#define BWHITE_FG 67
#define BRED_FG 68
#define BYELLOW_FG 69
#define BGREEN_FG 70
#define BCYAN_FG 71
#define BBLUE_FG 72
#define BMAGENTA_FG 73
#define NWHITE_FG 74
#define NRED_FG 75
#define NYELLOW_FG 76
#define NGREEN_FG 77
#define NCYAN_FG 78
#define NBLUE_FG 79
#define NMAGENTA_FG 80
#define DWHITE_FG 81
#define DRED_FG 82
#define DYELLOW_FG 83
#define DGREEN_FG 84
#define DCYAN_FG 85
#define DBLUE_FG 86
#define DMAGENTA_FG 87


#define BBLACK_FG 66

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
    double redTint = 1;
    double greenTint = 1;
    double blueTint = 1;
private:

    
    void setColor(short index, double bright, double redMod, double greenMod, double blueMod);
    void clipColors();
    
    
    
    
};
