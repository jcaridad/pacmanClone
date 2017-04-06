//
//  character.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "character.hpp"

Character::Character()
:m_maze(nullptr)
,m_speed(1.0f)
,m_nextDirection(0,0)
,m_currentDirection(1,0){
    
    
}
void Character::setMaze(Maze *maze){
    m_maze = maze;
}
void Character::setDirection(sf::Vector2i direction){
    m_nextDirection = direction;
}
sf::Vector2i Character::getDirection() const{
    return m_currentDirection;
}

void Character::update(sf::Time delta){
    //m_currentDirection = m_nextDirection;
}


void Character::setSpeed(float speed){
    m_speed = speed;
}

float Character::getSpeed() const{
    return m_speed;
}
