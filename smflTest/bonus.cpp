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
    m_visual.setOrigin(15, 15);
    setFruit(Apple);
}

void Bonus::setFruit(Fruit fruit){
    if(fruit == Apple){
        //check setTexture Params
        //m_visual.setTexture(32, 0, 30, 30);
    }
    else if(fruit == Orange){
        //m_visual.setTexture();
    }
    else if (fruit == Cherry){
        //m_visual.setTexture();
    }
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(m_visual, states);
}
