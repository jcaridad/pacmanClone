//
//  maze.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/29/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "maze.hpp"
#include "dot.hpp"
#include "define.h"
#include <cmath>

using namespace std;

Maze::Maze()
:m_mazeSize(0,0){
    
}


void Maze::loadLevel(string fileName){
    sf::Image levelData;
    
    if(!levelData.loadFromFile("/Users/jymarcaridad/ClassCodes/smflTest/smflTest/assets/levels/" + fileName + ".png")){
        throw runtime_error("Failed to load (" + fileName + ")");
    }
    m_mazeSize = sf::Vector2i(levelData.getSize());
    
    if(m_mazeSize.x < 15 || m_mazeSize.y < 15){
        throw runtime_error("The loaded level is too small (min 15 cells large)");
    }
    
    for(unsigned int y = 0; y < m_mazeSize.y; y++){
        for(unsigned int x = 0; x < m_mazeSize.x; x++){
            sf::Color cellData = levelData.getPixel(x, y);
            
            if(cellData == sf::Color::Black){
                m_mazeData.push_back(Wall);
            }
            else if(cellData == sf::Color::White){
                m_mazeData.push_back(Dot);
            }
            else if(cellData == sf::Color::Green){
                m_mazeData.push_back(SuperDot);
            }
            else if(cellData == sf::Color::Blue){
                m_pacManPosition = sf::Vector2i(x,y);
                m_mazeData.push_back(Empty);
            }
            else if(cellData == sf::Color::Red){
                m_ghostPositions.push_back(sf::Vector2i(x,y));
                m_mazeData.push_back(Empty);
            }
            else{
                m_mazeData.push_back(Empty);
            }
        }
    }
    
    m_renderTexture.create(CELLSIZE_W * m_mazeSize.x, CELLSIZE_H * m_mazeSize.y);
    m_renderTexture.clear(sf::Color::Black);
    
    m_renderTexture.display();
    
    for(unsigned int i = 0; i < m_mazeData.size(); i++){
        sf::Vector2i position = indexToPosition(i);
    
        if(m_mazeData[i] == Wall){
            sf::RectangleShape wall;
            wall.setSize(sf::Vector2f(CELLSIZE_W,CELLSIZE_H));
            wall.setFillColor(sf::Color::Blue);
            wall.setPosition(CELLSIZE_W*position.x, CELLSIZE_H*position.y);
            m_renderTexture.draw(wall);
        }
    }
}

void Maze::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sf::Sprite(m_renderTexture.getTexture()), states);
    
    static sf::CircleShape dot = getDot();
    static sf::CircleShape superDot = getSuperDot();
    
    for(unsigned int i = 0; i < m_mazeData.size(); i++){
        sf::Vector2i position = indexToPosition(i);
        if(m_mazeData[i] == Dot){
            dot.setPosition(CELLSIZE_W*position.x + 8, CELLSIZE_H*position.y + 8);
            target.draw(dot,states);
        }
        else if(m_mazeData[i] == SuperDot){
            superDot.setPosition(CELLSIZE_W*position.x + 8, CELLSIZE_H*position.y + 8);
            target.draw(superDot, states);
        }
    }
}


sf::Vector2i Maze::getSize() const
{
    return m_mazeSize;
}

sf::Vector2i Maze::getPacManPosition() const{
    return m_pacManPosition;
}

vector<sf::Vector2i> Maze::getGhostPositions()  const{
    return m_ghostPositions;
}

size_t Maze::positionToIndex(sf::Vector2i position) const{
    return position.y * m_mazeSize.x + position.x;
}

sf::Vector2i Maze::indexToPosition(size_t index) const{
    sf::Vector2i position;
    
    position.x = index % m_mazeSize.x;
    position.y = index / m_mazeSize.x;
    
    return position;
}

sf::Vector2i Maze::mapPixelToCell(sf::Vector2f pixel) const{
    sf::Vector2i cell;
    cell.x = floor(pixel.x / 32.f);
    cell.y = floor(pixel.y / 32.f);
    
    return cell;
}
sf::Vector2f Maze::mapCellToPixel(sf::Vector2i cell) const{
    sf::Vector2f pixel;
    pixel.x = cell.x * CELLSIZE_W + 8;
    pixel.y = cell.y * CELLSIZE_H + 8;
    
    return pixel;
}
