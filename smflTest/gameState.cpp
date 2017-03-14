//
//  gameState.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/6/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "gameState.hpp"

GameState::GameState(Game* game)
:m_game(game){
}

NoCoinState::NoCoinState(Game* game)
:GameState(game){
    
}

Game * GameState::getGame() const{
    return m_game;
}
void NoCoinState::insertCoin(){
    
}
void NoCoinState::pressButton(){
    
}
void NoCoinState::moveStick(sf::Vector2i direction){
    
}
void NoCoinState::update(sf::Time delta){
    
}
void NoCoinState::draw(sf::RenderWindow& window){
    
}
