//
//  pacman.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef pacman_hpp
#define pacman_hpp

#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "animator.hpp"

/**
 * Pacman Class
 * This Class Inherits from the Character Class. It focuses on all of Pac-Man/QuackMan's attributes and behavior such as, Animation Sprites, Running and Dying Animation, and Death.
 * @see Character Class
 */
class Pacman : public Character{
    
public:
    /**
     * A Pacman Constructor
     * Initiates the following member variables
     * - m_visual
     * - m_isDead
     * - m_isDying
     * Also uploads animation frames data into the animation sprites
     * - m_runAnimator
     * - m_dieAnimator
     * 
     * @param a_texture the texture sheet
     */
    Pacman(sf::Texture& a_texture);
    
    /**
     * This function ensure that the Pac-Man/QuackMan death animation plays and indicate that Player is dead
     */
    void die();
    
    /**
     * This function is a get function for m_isDying
     *
     * @return returns true dying animation is currently playing
     */
    bool isDying() const;
    
    /**
     * This function is a get function for m_isDead
     *
     * @return returns whether the player is dead or not
     */
    bool isDead() const;
    
    /**
     * This function checks the Player's current status in game (Dead or Alive) and plays the animation according to it's current state
     *
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
    /**
     * This function restarts Pac-Man/QuackMan's Animation back to it's running state
     */
    void reset();
private:
    
    /**
     * This private function renders the current animated sprite into the map
     *
     * @param a_target the render window instance
     * @param a_states the state that the sf::RenderTarget Instance is in
     */
    void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;
    
    /**
     * A private boolean variable
     * Indicates if m_dieAnimator is playing
     */
    bool m_isDying;
    
    /**
     * A private boolean variable
     * Indicates if Pac-Man/QuackMan is dead
     */
    bool m_isDead;
    
    /**
     * A private sf::Sprite variable
     * The sprite entity that is being rendered into the window
     * @see sf::Sprite: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php
     */
    sf::Sprite m_visual;
    
    /**
     * A private Animator instance
     * Holds the Pac-Man/QuackMan's running animation
     */
    Animator m_runAnimator;
    
    /**
     * A private Animator instance
     * Holds the Pac-Man/QuackMan's dying animation
     */
    Animator m_dieAnimator;
};

#endif /* pacman_hpp */
