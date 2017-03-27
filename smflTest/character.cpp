//
//  character.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "character.hpp"

Character::Character()
:m_speed(1.0f){
    
}

void Character::setSpeed(float speed){
    m_speed = speed;
}

float Character::getSpeed() const{
    return m_speed;
}
