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

class Character: public sf::Drawable, public sf::Transformable{
  
public:
    Character();
    
    virtual void update(sf::Time delta);
    void setDirection(sf::Vector2i direction);
    sf::Vector2i getDirection() const;
    void setMaze(Maze* maze);
    void setSpeed(float speed);
    float getSpeed() const;
    
    bool willMove() const;
    
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
