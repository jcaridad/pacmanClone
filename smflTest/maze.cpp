//
//  maze.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/29/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "maze.hpp"
#include "dot.hpp"
#include "bonus.hpp"
#include "define.h"
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

Maze::Maze(sf::Texture& texture )
:m_mazeSize(0,0)
,m_texture(texture){
    
}


void Maze::loadLevel(string fileName){
    
    m_mazeSize = sf::Vector2i(0, 0);
    m_mazeData.clear();
    
    cout<<m_mazeData.size()<<endl;
    
    m_pacManPosition = sf::Vector2i(0, 0);
    m_ghostPositions.clear();
    
    sf::Image levelData;
    //load up map images
    if(!levelData.loadFromFile("/Users/jymarcaridad/ClassCodes/smflTest/smflTest/assets/levels/"+ fileName +".png")){
        throw runtime_error("Failed to load (" + fileName + ")");
    }
    m_mazeSize = sf::Vector2i(levelData.getSize());
    
    if(m_mazeSize.x < 15 || m_mazeSize.y < 15){
        throw runtime_error("The loaded level is too small (min 15 cells large)");
    }
    
    //Reads image data
    //Translates image pixels into maze data according to color
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
            else if(cellData == sf::Color::Magenta){
                m_respawnPosition = sf::Vector2i(x,y);
                m_mazeData.push_back(Bonus);
            }
            else{
                m_mazeData.push_back(Empty);
            }
        }
    }
    
    cout<<m_mazeData.size()<<endl;
    
    m_renderTexture.create(CELLSIZE_W * m_mazeSize.x, CELLSIZE_H * m_mazeSize.y);
    m_renderTexture.clear(sf::Color::Black);
    
    //load up map textures
    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(CELLSIZE_W, CELLSIZE_H));
    wall.setFillColor(sf::Color::Blue);
    
    sf::Sprite border(m_texture);
    border.setTextureRect(sf::IntRect(8, 0, 8, 16));
    border.setOrigin(0, 8);
    
    sf::Sprite innerCorner(m_texture);
    innerCorner.setTextureRect(sf::IntRect(0, 0, 8, 8));
    innerCorner.setOrigin(0, 8);
    
    sf::Sprite outerCorner(m_texture);
    outerCorner.setTextureRect(sf::IntRect(0, 8, 8, 8));
    outerCorner.setOrigin(0, 8);
    
    m_renderTexture.display();
    
    //read all maze data to render the corresponding sprite
    for(unsigned int i = 0; i < m_mazeData.size(); i++){
        sf::Vector2i position = indexToPosition(i);
    
        if(isWall(position)){
            wall.setPosition(CELLSIZE_W * position.x, CELLSIZE_H * position.y);
            m_renderTexture.draw(wall);
            
            border.setPosition(mapCellToPixel(position));
            innerCorner.setPosition(mapCellToPixel(position));
            outerCorner.setPosition(mapCellToPixel(position));
            
            if(!isWall(position + sf::Vector2i(1, 0))){
                border.setRotation(0);
                m_renderTexture.draw(border);
            }
            if(!isWall(position + sf::Vector2i(0, 1))){
                border.setRotation(90);
                m_renderTexture.draw(border);
            }
            if(!isWall(position + sf::Vector2i(-1, 0))){
                border.setRotation(180);
                m_renderTexture.draw(border);
            }
            if(!isWall(position + sf::Vector2i(0, -1))){
                border.setRotation(270);
                m_renderTexture.draw(border);
            }
            if (isWall(position + sf::Vector2i(1, 0)) && isWall(position + sf::Vector2i(0, -1))){
                innerCorner.setRotation(0);
                m_renderTexture.draw(innerCorner);
            }
            
            if (isWall(position + sf::Vector2i(0, 1)) && isWall(position + sf::Vector2i(1, 0))){
                innerCorner.setRotation(90);
                m_renderTexture.draw(innerCorner);
            }
            if (isWall(position + sf::Vector2i(-1, 0)) && isWall(position + sf::Vector2i(0, 1))){
                innerCorner.setRotation(180);
                m_renderTexture.draw(innerCorner);
            }
            if (isWall(position + sf::Vector2i(0, -1)) && isWall(position + sf::Vector2i(-1, 0))){
                innerCorner.setRotation(270);
                m_renderTexture.draw(innerCorner);
            }
            if (!isWall(position + sf::Vector2i(1, 0)) && !isWall(position + sf::Vector2i(0, -1))){
                outerCorner.setRotation(0);
                m_renderTexture.draw(outerCorner);
            }
            if (!isWall(position + sf::Vector2i(0, 1)) && !isWall(position + sf::Vector2i(1, 0))){
                outerCorner.setRotation(90);
                m_renderTexture.draw(outerCorner);
            }
            if (!isWall(position + sf::Vector2i(-1, 0)) && !isWall(position + sf::Vector2i(0, 1))){
                outerCorner.setRotation(180);
                m_renderTexture.draw(outerCorner);
            }
            if (!isWall(position + sf::Vector2i(0, -1)) && !isWall(position + sf::Vector2i(-1, 0))){
                outerCorner.setRotation(270);
                m_renderTexture.draw(outerCorner);
            }
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
            dot.setPosition(CELLSIZE_W * position.x + 8, CELLSIZE_H * position.y + 8);
            target.draw(dot,states);
        }
        else if(m_mazeData[i] == SuperDot){
            superDot.setPosition(CELLSIZE_W * position.x + 8, CELLSIZE_H * position.y + 8);
            target.draw(superDot, states);
        }
        
    }
}


sf::Vector2i Maze::getSize() const{
    return m_mazeSize;
}

sf::Vector2i Maze::getPacManPosition() const{
    return m_pacManPosition;
}

vector<sf::Vector2i> Maze::getGhostPositions()  const{
    return m_ghostPositions;
}

sf::Vector2i Maze::getRespawnPosition() const{
    return m_respawnPosition;
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
    cell.x = floor(pixel.x / 16.f);
    cell.y = floor(pixel.y / 16.f);
    
    return cell;
}
sf::Vector2f Maze::mapCellToPixel(sf::Vector2i cell) const{
    sf::Vector2f pixel;
    pixel.x = cell.x * CELLSIZE_W + 8;
    pixel.y = cell.y * CELLSIZE_H + 8;
    
    return pixel;
}

bool Maze::isWall(sf::Vector2i position) const{
    if(position.x < 0 || position.y < 0 || position.x >= m_mazeSize.x || position.y >= m_mazeSize.y){
        return false;
    }
    return m_mazeData[positionToIndex(position)] == Wall;
}

bool Maze::isDot(sf::Vector2i position) const{
    return m_mazeData[positionToIndex(position)] == Dot;
}

bool Maze::isSuperDot(sf::Vector2i position) const{
    return m_mazeData[positionToIndex(position)] == SuperDot;
}

bool Maze::isBonus(sf::Vector2i position) const{
    return m_mazeData[positionToIndex(position)] == Bonus;
}

void Maze::pickObject(sf::Vector2i position){
    assert(!isWall(position));
    m_mazeData[positionToIndex(position)] = Empty;
}

int Maze::getRemainingDots() const{
    int remainingDots = 0;
    
    for(unsigned int i = 0; i < m_mazeData.size(); i++){
        if(m_mazeData[i] == Dot || m_mazeData[i] == SuperDot){
            remainingDots++;
        }
    }
    return remainingDots;
}
