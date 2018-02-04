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
    setColor(BBLACK_FG, 0, 1., 1., 1.);
    
    for (int i = 0; i < 3; i++) {
        double brightActual = brightness / (pow(2, i) );
        setColor(BWHITE_FG + (7 * i), brightActual, 1., 1., 1. );
        setColor(BWHITE_FG + (7 * i) + 1, brightActual, 1., 0, 0 );
        setColor(BWHITE_FG + (7 * i) + 2, brightActual, 1., 1., 0);
        setColor(BWHITE_FG + (7 * i) + 3, brightActual, 0, 1., 0);
        setColor(BWHITE_FG + (7 * i) + 4, brightActual, 0, 1., 1. );
        setColor(BWHITE_FG + (7 * i) + 5, brightActual, 0, 0, 1. );
        setColor(BWHITE_FG + (7 * i) + 6, brightActual, 1., 0, 1. );
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
    
    init_color(index, r, g, b);
}

