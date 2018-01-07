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

#include "options.h"

void options::initOptions()
{
    ga_allowScumming = false;
    ga_bufferPause = true;
    ga_bufferWait = 3000;
    ga_casualMode = false;
    ga_trackAchievements = true;
    
    gr_bufferSize = 500;
    gr_displaySplashScreens = true;
    gr_drawEnemyAttacks = true;
    gr_drawPlayerAttacks = true;
    gr_drawScreenEffects = true;
    gr_drawLightLevel = true;
    gr_highlightTraits = true;

}


bool options::checkOptions()
{
    bool badOptions = false;
    
    if (ga_trackAchievements) {
        if (ga_allowScumming) {
            ga_trackAchievements = false;
            badOptions = true;
        }
        if (ga_casualMode) {
            ga_trackAchievements = false;
            badOptions = true;
        }
    }
    
    
    return badOptions;
}
