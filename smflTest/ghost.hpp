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
#include <cmath>

#include "animator.hpp"
#include "character.hpp"
#include "pacman.hpp"

class Ghost: public Character{
public:
    enum State{
        Strong,
        Weak
    };
    
    Ghost(sf::Texture& a_texture, Pacman* a_pacman);
    void setWeak(sf::Time a_duration);
    bool isWeak() const;
    
    void update(sf::Time a_delta);
    
protected:
    void changeDirection();
private:
    void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;
    
    bool m_isWeak;
    sf::Time m_weakStateTimer;
    
    Pacman* m_pacMan;
    sf::Sprite m_visual;
    
    Animator m_strongAnimator;
    Animator m_weakAnimator;
    
    
};

#endif /* ghost_hpp */
