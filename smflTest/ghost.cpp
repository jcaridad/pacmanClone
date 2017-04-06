//
//  ghost.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "ghost.hpp"


Ghost::Ghost(sf::Texture& texture)
:m_visual(texture)
,m_isWeak(false)
,m_weakStateTimer(sf::Time::Zero)
{
    setOrigin(20, 20);
    
    setScale(0.50, 0.50);
    
    m_strongAnimator.addFrame(sf::IntRect(40, 32, 40, 40));
    //m_strongAnimator.addFrame(sf::IntRect(80, 32, 40, 40));
    
    m_weakAnimator.addFrame(sf::IntRect(40, 72, 40, 40));
    // m_weakAnimator.addFrame(sf::IntRect(80, 72, 40, 40));
    
    m_strongAnimator.play(sf::seconds(0.25), true);
    m_weakAnimator.play(sf::seconds(1), true);
}


void Ghost::setWeak(sf::Time duration){
    m_isWeak = true;
    m_weakStateTimer = duration;
}

bool Ghost::isWeak() const{
    return m_isWeak;
}

void Ghost::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(m_visual, states);
}

void Ghost::update(sf::Time delta){
    
    if (m_isWeak)
    {
        m_weakStateTimer -= delta;
        
        if (m_weakStateTimer <= sf::Time::Zero)
        {
            m_isWeak = false;
            m_strongAnimator.play(sf::seconds(0.25), true);
        }
    }
    
    if(!m_isWeak){
        m_strongAnimator.update(delta);
        m_strongAnimator.animate(m_visual);
    }
    else{
        m_weakAnimator.update(delta);
        m_weakAnimator.animate(m_visual);
    }
}
