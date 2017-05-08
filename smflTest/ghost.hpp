//
//  ghost.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef ghost_hpp
#define ghost_hpp

#include <stdio.h>
#include <cmath>

#include "animator.hpp"
#include "character.hpp"
#include "pacman.hpp"

/**
 * Ghost Class
 * This Class Inherits from the Character Class. It focuses on the two important ghost attributes: the Strong and Weak Animation, and the Pathfinding Algorithm
 * @see Character Claas
 */
class Ghost: public Character{
public:
    /**
     * An enum Type
     * Indicates what state the ghost is in
     */
    enum State{
        Strong, /**< Strong State: Can Kill Player */
        Weak /**< WeakState: Can be killed by Player */
    };
    
    /**
     * A Ghost Constructor
     * Initiates the following member variables
     * - m_visual
     * - m_isWeak
     * - m_weakStateTimer
     * - m_pacMan
     * Also uploads animation frames data into the animation sprites
     * - m_strongAnimator
     * - m_weakAnimator
     */
    Ghost(sf::Texture& a_texture, Pacman* a_pacman);

    /**
     * This function set the ghost into the weak state for a certain amount of time which makes it vulnerable to Pac-Man/QuackMan Collision
     *
     * @param a_duration the length in sf::Seconds that the ghost is in wthe weak state
     */
    void setWeak(sf::Time a_duration);
    
    /**
     * This is a get function for m_isWeak
     *
     * @return returns true if the ghost is in the weak state
     */
    bool isWeak() const;
    
    /**
     * This function checks the Ghost's current status in game (Dead or Alive) and plays the animation according to it's current state
     *
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
protected:
    
    /**
     * This function holds the path finding AI for the ghosts. It has a static vector that holds 4 directions and stores it in a map container from best to worst.
     * Gets the angle between pacman and ghost and uses that to decide and rank which direction to take from best to worst if it is in the Strong State. During the Weak State it uses the same ranking but reads it backwards(worst to best).
     *
     */
    void changeDirection();
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
     * Indicates whether the ghost is in the weak state or not
     */
    bool m_isWeak;
    
    /**
     * A private sf::Time variable
     * The duration of the ghost being in the weak state
     * @see sf::Time: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Time.php
     */
    sf::Time m_weakStateTimer;
    
    /**
     * A private Pacman instance
     * The current instance of the player that is on the map
     */
    Pacman* m_pacMan;
    
    /**
     * A private sf::Sprite variable
     * The sprite entity that is being rendered into the window
     * @see sf::Sprite: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php
     */
    sf::Sprite m_visual;
    
    /**
     * A private Animator instance
     * Holds the ghost's (Strong State) Animation
     */
    Animator m_strongAnimator;
    
    /**
     * A private Animator instance
     * Holds the ghost's (Weak State) Animation
     */
    Animator m_weakAnimator;
    
    
};

#endif /* ghost_hpp */
