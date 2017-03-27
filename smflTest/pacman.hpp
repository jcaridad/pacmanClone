//
//  pacman.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef pacman_hpp
#define pacman_hpp

#include <SFML/Graphics.hpp>

#include "character.hpp"

class Pacman : public Character{
    
public:
    Pacman(sf::Texture& texture);
    void die();
    bool isDead() const;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool m_isDead;
    sf::Sprite m_visual;
};

#endif /* pacman_hpp */
