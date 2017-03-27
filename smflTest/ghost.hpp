//
//  ghost.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef ghost_hpp
#define ghost_hpp

#include <stdio.h>

#include "character.hpp"
#include "pacman.hpp"

class Ghost: public Character{
public:
    enum State{
        Strong,
        Weak
    };
    
    Ghost(sf::Texture& texture, Pacman* pacman);
    void setWeak(sf::Time duration);
    bool isWeak() const;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    bool m_isWeak;
    sf::Time m_weakStateTimer;
    sf::Sprite m_visual;
    
    
};

#endif /* ghost_hpp */
