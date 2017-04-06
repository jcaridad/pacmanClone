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
    
private:
    float m_speed;
    Maze* m_maze;
    sf::Vector2i m_currentDirection;
    sf::Vector2i m_nextDirection;
    
};



#endif /* character_hpp */
