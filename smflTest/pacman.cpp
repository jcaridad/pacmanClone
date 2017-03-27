//
//  pacman.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "pacman.hpp"

Pacman::Pacman(sf::Texture& texture)
:m_visual(texture), m_isDead(false){
    //set origin depending on sprite size
    setOrigin(20, 20);
}

void Pacman::die(){
    m_isDead = true;
}

bool Pacman::isDead() const{
    return m_isDead;
}

void Pacman::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    
    if(!m_isDead){
        target.draw(m_visual, states);
    }
    
}
