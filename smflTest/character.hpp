//
//  character.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include <SFML/Graphics.hpp>

#include "maze.hpp"
/**
 * Character Class
 * Parent Class to Pacman and Ghost. Inherits from sf::Drawable and sf::Transformable. sf::Transformable can be used as a base class. It is often combined with sf::Drawable – that's what SFML's sprites, texts and shapes do.
 * This is where most of the Character to Maze interaction is happening. Wall Collision, Tunnels, Character Speed, and Movement Direction are handled in this Class
 * @see sf::Transformable: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Transformable.php
 * @see sf::Drawable: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Drawable.php
 */
class Character: public sf::Drawable, public sf::Transformable{
  
public:
    /**
     * A Character Constructor
     * Initiates the following member variables
     * - m_maze
     * - m_speed
     * - m_currentDirection
     * - m_nextDirection
     * - m_prevIntersecion
     */
    Character();
    
    /**
     * A virtual function
     *
     * @param a_delta the current time
     * @see Pacman Class
     * @see Ghost Class
     */
    virtual void update(sf::Time a_delta);
    
    /**
     * This function takes a sfml integer vector as a position and sets which direction the character needs to go. This function also processes all interaction that the character has with the map such ass Wall Collision, and the Tunnel. It also controls the Ghost's movements
     *
     * @param a_direction the direction the character is heading
     */
    void setDirection(sf::Vector2i a_direction);
    
    /**
     * This function is a get function for the m_currentDirection which is a private variable
     *
     * @return Returns the direction that the character is taking in the map
     */
    sf::Vector2i getDirection() const;
    
    /**
     * This function assigns the current game instance to the character class
     *
     * @param a_maze the maze instance
     */
    void setMaze(Maze* a_maze);
    
    /**
     * This function registers how fast the character moves around the map
     *
     * @param a_speed the character's movement speed
     */
    void setSpeed(float a_speed);
    
    /**
     * This function is a get function for the m_speed which is a private variable
     *
     * @return Returns the character's movement speed
     */
    float getSpeed() const;
    
    /**
     * This function checks wheter the next direction is a valid position that the character can go to
     *
     * @return Returns true if the next direction not a wall
     */
    bool willMove() const;
    
    /**
     * This function creates a rectangle bound around the character sprite which helps detect collision
     *
     * @return Returns the position/rotation/scale/origin of the collision box
     */
    sf::FloatRect getCollision() const;
    
protected:
    
    /**
     * This is a virtual function that the ghost class uses for it's pathfinding AI
     *
     * @see Ghost Class
     */
    virtual void changeDirection(){};
    
private:
    /**
     * A private float variable
     * Represents the character's movement speed
     */
    float m_speed;
    
    /**
     * A private Maze instance
     * Pointer for the current Maze instance
     */
    Maze* m_maze;
    
    /**
     * A private sf::Vector2i variable
     * The current direction that the character is moving towards
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    sf::Vector2i m_currentDirection;
    
    /**
     * A private sf::Vector2i variable
     * The next direction that the character is taking
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    sf::Vector2i m_nextDirection;
    
    /**
     * A private sf::Vector2i variable
     * Holds the position of the last intersection in the map that the character crossed
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    sf::Vector2i m_prevIntersection;
    
    /**
     * A private std::array container
     * holds all the possible direction that the Ghost can take from best to worst
     * @see Character::update()
     */
    array<bool, 4> m_availableDirections;
    
};



#endif /* character_hpp */
