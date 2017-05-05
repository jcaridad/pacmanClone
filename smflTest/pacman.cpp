//
//  pacman.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "pacman.hpp"

Pacman::Pacman(sf::Texture& a_texture)
:m_visual(a_texture)
,m_isDead(false)
,m_isDying(false){
    //set origin depending on sprite size
    setOrigin(10, 10);
    
    //Running Animation
    m_runAnimator.addFrame(sf::IntRect(0, 16, 20, 20));
    m_runAnimator.addFrame(sf::IntRect(0, 36, 20, 20));
    
    //Dying animation
    m_dieAnimator.addFrame(sf::IntRect(0, 16, 20, 20));
    m_dieAnimator.addFrame(sf::IntRect(0, 36, 20, 20));
    m_dieAnimator.addFrame(sf::IntRect(0, 56, 20, 20));
    m_dieAnimator.addFrame(sf::IntRect(20, 56, 20, 20));
    m_dieAnimator.addFrame(sf::IntRect(40, 56, 20, 20));
    m_dieAnimator.addFrame(sf::IntRect(60, 56, 20, 20));
    m_dieAnimator.addFrame(sf::IntRect(80, 156, 20, 20));
   
    m_runAnimator.play(sf::seconds(0.5), true);
}

void Pacman::die(){
    if(!m_isDying){
        m_dieAnimator.play(sf::seconds(1), false);
        m_isDead = true;
    }
}

bool Pacman::isDying() const{
    return m_isDying;
}
bool Pacman::isDead() const{
    return m_isDead;
}

void Pacman::reset(){
    m_isDying = false;
    m_isDead = false;
    
    m_runAnimator.play(sf::seconds(0.75), true);
    m_runAnimator.animate(m_visual);
}
void Pacman::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const{
    a_states.transform *= getTransform();
    if(!m_isDead){
        a_target.draw(m_visual, a_states);
    }
}

void Pacman::update(sf::Time a_delta){
    
    if (!m_isDead && !m_isDying)
    {
        m_runAnimator.update(a_delta);
        m_runAnimator.animate(m_visual);
    }
    else
    {
        m_dieAnimator.update(a_delta);
        m_dieAnimator.animate(m_visual);
        
        if (!m_dieAnimator.isPlaying())
        {
            m_isDying = false;
            m_isDead = true;
        }
    }
    Character::update(a_delta);
}
