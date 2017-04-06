//
//  dot.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "dot.hpp"


sf::CircleShape getDot(){
    sf::CircleShape dot;
    
    dot.setRadius(2);
    dot.setFillColor(sf::Color::White);
    dot.setOrigin(1, 1);
    
    return dot;
}

sf::CircleShape getSuperDot(){
    sf::CircleShape superDot;
    
    superDot.setRadius(4);
    superDot.setFillColor(sf::Color::White);
    superDot.setOrigin(2, 2);
    
    return superDot;
}
