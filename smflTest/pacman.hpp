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
#include "animator.hpp"

class Pacman : public Character{
    
public:
    Pacman(sf::Texture& a_texture);
    void die();
    bool isDying() const;
    bool isDead() const;
    
    void update(sf::Time a_delta);
    
    void reset();
private:
    void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;
    bool m_isDying;
    bool m_isDead;
    sf::Sprite m_visual;
    
    Animator m_runAnimator;
    Animator m_dieAnimator;
};

#endif /* pacman_hpp */
