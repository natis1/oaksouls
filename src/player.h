/*
 * Oaksouls ~ A difficult roguelike about a tree spirit.
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

#pragma once

// user picks a direction and attack goes there
#define TARGETTING_DIRECTION 1
// user picks a direction and charges that way
#define TARGETTING_DIRECTION_CHARGED 2
// user picks a direction and charges that way but stops after hitting the first enemy.
#define TARGETTING_DIRECTION_BLOCKED 3
// attack hits all enemies near them
#define TARGETTING_AOE 9
// attack hits the nearest enemy
#define TARGETTING_NEARESTENEMY 10
// attack hits a user chosen spot
#define TARGETTING_USERSPOT 11
// attack applies to the user
#define TARGETTING_USER 30

// effects that can be applied
#define EFFECT_DAMAGE 0
#define EFFECT_POISON 1


struct attack {
    
    
    int chargeTime;
    
    // How long the effect lasts in the environment
    int effectTime;
    int cooldownTime;
    
    
    int targetting;
    
    /*
     * Determines the maximum distance the attack can hit or the charge can travel
     * 
     */
    int range;
    
    /*
     * determines the width if using any direction targetting
     * nothing with AOE targetting
     * the maximum number of enemies hit with nearest enemy targetting.
     * the area of effect of userspot targetting
     * 
     */
    int size;
    
    // cost matters to plants that use energy on attacks
    int cost;
    
    // damage or magnitude or whatever. Negative values apply the opposite (EG healing instead of damage)
    double baseEffectSize;
    // how much the effect scales with the player's damage stat
    double effectScaleFactor;
    // 
    
    
    
};


class player
{
public:
    /**
     * Default constructor
     */
    player();
    
    
    // Abilities return error if they fail for whatever reason
    int ability1();
    int ability2();
    int ability3();
    int ability4();
    
    
    
private:
    
    void applyTraits();
    int health;
    int damage;
    
    
};
