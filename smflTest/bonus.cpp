//
//  bonus.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "bonus.hpp"

Bonus::Bonus(sf::Texture& a_texture)
:m_visual(a_texture){
    //15x15 is origin from texture size
    m_visual.setOrigin(8, 8);
    setFruit(Apple);
}

void Bonus::setFruit(Fruit a_fruit){
    if (a_fruit == Banana){
        m_visual.setTextureRect(sf::IntRect(16, 0, 15, 15));
    }
    else if (a_fruit == Apple){
        m_visual.setTextureRect(sf::IntRect(31, 0, 15, 15));
    }
    else if (a_fruit == Cherry){
        m_visual.setTextureRect(sf::IntRect(46, 0, 15, 15));
    }
}

void Bonus::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const{
    a_states.transform *= getTransform();
    a_target.draw(m_visual, a_states);
}
