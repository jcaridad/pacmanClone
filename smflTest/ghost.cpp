//
//  ghost.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "ghost.hpp"



Ghost::Ghost(sf::Texture& a_texture, Pacman* a_pacman)
:m_visual(a_texture)
,m_isWeak(false)
,m_weakStateTimer(sf::Time::Zero)
,m_pacMan(a_pacman){
    setOrigin(10, 10);
    //strong animation
    m_strongAnimator.addFrame(sf::IntRect(20, 16, 20, 20));
    //weakAnimation
    m_weakAnimator.addFrame(sf::IntRect(20, 36, 20, 20));
    
    m_strongAnimator.play(sf::seconds(0.25), true);
    m_weakAnimator.play(sf::seconds(1), true);
}


void Ghost::setWeak(sf::Time a_duration){
    m_isWeak = true;
    m_weakStateTimer = a_duration;
}

bool Ghost::isWeak() const{
    return m_isWeak;
}

void Ghost::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const{
    a_states.transform *= getTransform();
    a_target.draw(m_visual, a_states);
}

void Ghost::update(sf::Time a_delta){
    
    if (m_isWeak){
        m_weakStateTimer -= a_delta;
        
        if (m_weakStateTimer <= sf::Time::Zero){
            m_isWeak = false;
            m_strongAnimator.play(sf::seconds(0.25), true);
        }
    }
    
    if(!m_isWeak){
        m_strongAnimator.update(a_delta);
        m_strongAnimator.animate(m_visual);
    }
    else{
        m_weakAnimator.update(a_delta);
        m_weakAnimator.animate(m_visual);
    }
    
    Character::update(a_delta);
}

void Ghost::changeDirection(){
    static sf::Vector2i directions[4] = {
        sf::Vector2i(1, 0),
        sf::Vector2i(0, 1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(0, -1)
    };
    
    map<float, sf::Vector2i> directionProb;
    
    //targeting algorithm
    float targetAngle;
    
    
    if(isWeak()){
        //gets distance how close pacman with the ghosts
        sf::Vector2f distance = m_pacMan->getPosition() -  getPosition();
        
        targetAngle = atan2(distance.x, distance.y) * (180/3.14);
        
        for (auto direction : directions){
            float directionAngle = atan2(direction.x, direction.y) * (180/3.14);
            
            //Normalize the angle difference
            float diff = 180 - abs(abs(directionAngle - targetAngle) - 180);
            
            directionProb[diff] = direction;
        }
        //iterate through the directionProb map from worst to best
        setDirection(directionProb.rbegin()->second);
        
        auto it = directionProb.rbegin();
        
        do{
            setDirection(it->second);
            it++;
        }
        while(!willMove());
    }
    else{
        sf::Vector2f distance = m_pacMan->getPosition() - getPosition();
        
        targetAngle = atan2(distance.x, distance.y) * (180/3.14);
        
        for (auto direction : directions){
            float directionAngle = atan2(direction.x, direction.y) * (180/3.14);
            
            //Normalize the angle difference
            float diff = 180 - abs(abs(directionAngle - targetAngle) - 180);
            
            directionProb[diff] = direction;
        }
        //iterate through the directionProb map from best to worst
        setDirection(directionProb.begin()->second);
        
        auto it = directionProb.begin();
        
        do{
            setDirection(it->second);
            it++;
        }
        while(!willMove());
    }
    
}

