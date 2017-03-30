//
//  maze.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/29/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "maze.hpp"

using namespace std;

Maze::Maze()
:m_mazeSize(0,0){
    
}


void Maze::loadLevel(string fileName){
    sf::Image levelData;
    
    if(!levelData.loadFromFile("/Users/jymarcaridad/ClassCodes/smflTest/smflTest/assets/levels" + fileName + ".png")){
        throw runtime_error("Failed to load (" + fileName + ")");
    }
    
    if(m_mazeSize.x < 15 || m_mazeSize.y < 15){
        throw runtime_error("The loaded level is too small (min 15 cells large)");
    }
    
    for(unsigned int y = 0; y < m_mazeSize.y; y++){
        for(unsigned int x = 0; x < m_mazeSize.x; x++){
            
        }
    }
}

void Maze::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    
}
