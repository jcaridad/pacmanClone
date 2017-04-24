//
//  bonus.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "bonus.hpp"

Bonus::Bonus(sf::Texture& texture)
:m_visual(texture){
    //15x15 is origin from texture size
    m_visual.setOrigin(8, 8);
    setFruit(Apple);
}

void Bonus::setFruit(Fruit fruit){
    if (fruit == Orange){
        m_visual.setTextureRect(sf::IntRect(16, 0, 15, 15));
    }
    else if (fruit == Apple){
        m_visual.setTextureRect(sf::IntRect(31, 0, 15, 15));
    }
    else if (fruit == Cherry){
        m_visual.setTextureRect(sf::IntRect(46, 0, 15, 15));
    }
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(m_visual, states);
}
