/*
 * It manages an options file I guess idk.
 * Copyright (C) 2017  Eli Stone  eli.stonium@gmail.com
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

class options
{
public:
    void initOptions();
    
    // Stops cheating, at least makes it a little bit harder by making sure someone doesn't scum options.
    bool checkOptions();

    // Gameplay options.
    
    // This option enables save without quitting, and disables deleting saves on loading games. It also turns off achievement tracking.
    bool ga_allowScumming;
    // Is everything unlocked from the start? Disables achievement tracking.
    bool ga_casualMode;
    // Are achievements tracked and awarded? Recommended to turn off if the player wishes to cheat.
    bool ga_trackAchievements;
    // Should the game pause after printing a message to the buffer? (continued with any button)
    bool ga_bufferPause;
    // How long should the game wait in miliseconds after printing a message if ga_bufferPause is false.
    unsigned int ga_bufferWait;
    // Graphical options.
    
    // Determines historical message buffer size. Increasing increases RAM usage at a rate of 1KB/6 messages. Minimum size is 1. Recommended: anything above 50
    unsigned int gr_bufferSize;
    // Should effects be drawn to indicate low heath or statuses?
    bool gr_drawScreenEffects;
    // Should effects be drawn to indicate enemy attacks?
    bool gr_drawEnemyAttacks;
    // Should effects be drawn to indicate player attacks?
    bool gr_drawPlayerAttacks;
    // Should effects be drawn to indicate light level? (Highly recommended)
    bool gr_drawLightLevel;
    // Should a splash screen be displayed upon entering an area?
    bool gr_displaySplashScreens;
    // This option highlights traits by their origin: Green for Green Algae, red for Opisthokonts, blue for all other groups. Useful for some achievements
    bool gr_highlightTraits;

    
};
