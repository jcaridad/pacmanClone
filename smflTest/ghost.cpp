//
//  ghost.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "ghost.hpp"


Ghost::Ghost(sf::Texture& texture)
:m_visual(texture)
,m_isWeak(false)
,m_weakStateTimer(sf::Time::Zero){
    setOrigin(20, 20);
}


void Ghost::setWeak(sf::Time duration){
    m_isWeak = true;
    m_weakStateTimer = duration;
}

bool Ghost::isWeak() const{
    return m_isWeak;
}
