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
 */
class Character: public sf::Drawable, public sf::Transformable{
  
public:
    /**
     * A Character Constructor
     * Initiates the following member classes
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
     */
    virtual void update(sf::Time a_delta);
    
    /**
     * This function takes a sfml integer vector as a position and sets which direction the character needs to go
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
     @return Returns the position/rotation/scale/origin of the collision box
     */
    sf::FloatRect getCollision() const;
    
protected:
    virtual void changeDirection(){};
    
private:
    float m_speed;
    Maze* m_maze;
    sf::Vector2i m_currentDirection;
    sf::Vector2i m_nextDirection;
    
    sf::Vector2i m_prevIntersection;
    array<bool, 4> m_availableDirections;
    
};



#endif /* character_hpp */
