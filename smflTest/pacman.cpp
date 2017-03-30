//
//  pacman.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "pacman.hpp"

Pacman::Pacman(sf::Texture& texture)
:m_visual(texture)
,m_isDead(false)
,m_isDying(false){
    //set origin depending on sprite size
    setOrigin(20, 20);
    
    m_runAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
    m_runAnimator.addFrame(sf::IntRect(0, 72, 40, 40));
    
    m_dieAnimator.addFrame(sf::IntRect(0, 32, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(0, 72, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(0, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(40, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(80, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(120, 112, 40, 40));
    m_dieAnimator.addFrame(sf::IntRect(160, 112, 40, 40));
    
    m_runAnimator.play(sf::seconds(0.25), true);
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

void Pacman::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    
    if(!m_isDead){
        target.draw(m_visual, states);
    }
    
}

void Pacman::update(sf::Time delta){
    
    if (!m_isDead && !m_isDying)
    {
        m_runAnimator.update(delta);
        m_runAnimator.animate(m_visual);
    }
    else
    {
        m_dieAnimator.update(delta);
        m_dieAnimator.animate(m_visual);
        
        if (!m_dieAnimator.isPlaying())
        {
            m_isDying = false;
            m_isDead = true;
        }
    }
}
