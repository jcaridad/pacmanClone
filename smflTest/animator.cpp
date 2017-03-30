//
//  animator.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/27/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "animator.hpp"

Animator::Animator()
:m_currentFrame(0)
,m_isPlaying(false)
,m_duration(sf::Time::Zero)
,m_loop(false){
    
}

void Animator::addFrame(sf::IntRect frame){
    m_frames.push_back(frame);
}

void Animator::play(sf::Time duration, bool loop){
    m_isPlaying = true;
    m_duration = duration;
    m_loop = true;
}
bool Animator::isPlaying() const{
    return m_isPlaying;
}

void Animator::update(sf::Time delta){
    if (!isPlaying())
        return;
    
    static sf::Time timeBuffer = sf::Time::Zero;
    timeBuffer += delta;
    
    sf::Time frameDuration = m_duration / static_cast<float>(m_frames.size());
    
    while (timeBuffer > frameDuration){
        m_currentFrame++;
        
        if (m_currentFrame == m_frames.size()){
            if (!m_loop){
                m_isPlaying = false;
            }
            m_currentFrame = 0;
        }
        timeBuffer -= frameDuration;
    }
}

void Animator::animate(sf::Sprite& sprite){
    sprite.setTextureRect(m_frames[m_currentFrame]);
}
