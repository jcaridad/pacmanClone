//
//  character.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//
#include <iostream>
#include <cmath>
#include <array>
#include "character.hpp"
#include "define.h"


Character::Character()
:m_maze(nullptr)
,m_speed(.25f)
,m_currentDirection(1,0)
,m_nextDirection(0,0)
,m_prevIntersection(0,0){

}
void Character::setMaze(Maze *a_maze){
    m_maze = a_maze;
}

void Character::setDirection(sf::Vector2i a_direction){
    m_nextDirection = a_direction;
}
sf::Vector2i Character::getDirection() const{
    return m_currentDirection;
}

bool Character::willMove() const{
    return !m_maze->isWall(m_prevIntersection + m_nextDirection);
}

sf::FloatRect Character::getCollision() const{
    sf::FloatRect bounds(3, 3, 18, 18);
    return getTransform().transformRect(bounds);
}

void Character::update(sf::Time a_delta){
    sf::Vector2f pixelPosition = getPosition();
    
    float pixelTraveled = getSpeed() * a_delta.asSeconds();
    
    sf::Vector2f nextPixelPosition = pixelPosition + sf::Vector2f(m_currentDirection) * pixelTraveled;
    setPosition(nextPixelPosition);
    
    sf::Vector2i cellPosition = m_maze->mapPixelToCell(pixelPosition);
    
    sf::Vector2f offset;
    offset.x = fmod(pixelPosition.x,CELLSIZE_W) - 8;
    offset.y = fmod(pixelPosition.y,CELLSIZE_H) - 8;
    
    //Wall Collision Detection
    if(m_maze->isWall(cellPosition + m_currentDirection)){
        if((m_currentDirection.x == 1 && offset.x > 0) ||
           (m_currentDirection.x == -1 && offset.x < 0)||
           (m_currentDirection.y == 1 && offset.y > 0) ||
           (m_currentDirection.y == -1 && offset.y < 0)){
            setPosition(m_maze->mapCellToPixel(cellPosition));
        }
    }
    
    //Tunnel Processing
    // x = -16 is a whole cell outside the screen to the left
    // x = 454 is a whole cell outside the right
    if(pixelPosition.x < -16){
        setPosition(454, pixelPosition.y);
    }
    else if(pixelPosition.x > 454){
        setPosition(-16, pixelPosition.y);
    }

    //Intersection Check
    //See if Player or Ghost can change direction
    if(!m_maze->isWall(cellPosition + m_nextDirection) && (m_currentDirection != m_nextDirection)){
        if((!m_currentDirection.y && (offset.x > -2 && offset.x < 2)) ||
           (!m_currentDirection.x && (offset.y > -2 && offset.y < 2))){
            setPosition(m_maze->mapCellToPixel(cellPosition));
            m_currentDirection = m_nextDirection;
        
            //Flip sprite depending on direction change
            if (m_currentDirection == sf::Vector2i(1, 0)){
                setRotation(0);
                setScale(-1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(0, 1)){
                setRotation(90);
                setScale(-1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(-1, 0)){
                setRotation(0);
                setScale(1, 1);
            }
            else if (m_currentDirection == sf::Vector2i(0, -1)){
                setRotation(90);
                setScale(1, 1);
            }
        }
    }
    static sf::Vector2i directions[4] = {
        sf::Vector2i(1, 0),
        sf::Vector2i(0, 1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(0, -1)
    };
    
    //Ghost Direction Change
    if (cellPosition != m_prevIntersection){
        if ((!m_currentDirection.y  && (offset.x > -2 && offset.x < 2)) ||
            (!m_currentDirection.x  && (offset.y > -2 && offset.y < 2))){
            array<bool, 4> availableDirections;
            
            int i = 0;
            for (auto direction : directions){
                availableDirections[i] = m_maze->isWall(cellPosition + direction);
                i++;
            }
            
            if (m_availableDirections != availableDirections){
                m_prevIntersection = cellPosition;
                m_availableDirections = availableDirections;
                
                changeDirection();
            }
        }
    }
}


void Character::setSpeed(float a_speed){
    m_speed = a_speed;
}

float Character::getSpeed() const{
    return m_speed;
}
