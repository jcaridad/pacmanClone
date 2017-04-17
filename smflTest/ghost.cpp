//
//  ghost.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "ghost.hpp"



Ghost::Ghost(sf::Texture& texture, Pacman* pacman)
:m_visual(texture)
,m_isWeak(false)
,m_weakStateTimer(sf::Time::Zero)
,m_pacMan(pacman){
    setOrigin(20/2, 20/2);
    
    //setScale(0.50, 0.50);
    
    m_strongAnimator.addFrame(sf::IntRect(40/2, 32/2, 40/2, 40/2));
    //m_strongAnimator.addFrame(sf::IntRect(80, 32, 40, 40));
    
    m_weakAnimator.addFrame(sf::IntRect(40/2, 72/2, 40/2, 40/2));
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
    
    Character::update(delta);
}

void Ghost::changeDirection()
{
    static sf::Vector2i directions[4] = {
        sf::Vector2i(1, 0),
        sf::Vector2i(0, 1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(0, -1)
    };
    
    map<float, sf::Vector2i> directionProb;
    
    float targetAngle;
    
    sf::Vector2f distance = m_pacMan->getPosition() - getPosition();
    
    targetAngle = atan2(distance.x, distance.y) * (180/3.14);
    
    for (auto direction : directions)
    {
        float directionAngle = atan2(direction.x, direction.y) * (180/3.14);
        
        //Normalize the angle difference
        float diff = 180 - abs(abs(directionAngle - targetAngle) - 180);
        
        directionProb[diff] = direction;
    }
    setDirection(directionProb.begin()->second);
    
    auto it = directionProb.begin();
    
    do
    {
        setDirection(it->second);
        it++;
    }
    while(!willMove());
}

