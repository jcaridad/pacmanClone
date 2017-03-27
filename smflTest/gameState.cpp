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

WonState::WonState(Game* game)
:GameState(game){
    
}
LostState::LostState(Game* game)
:GameState(game){
    
}
PlayingState::PlayingState(Game* game)
:GameState(game){
    
}
GetReadyState::GetReadyState(Game* game)
:GameState(game){
    
}

Game * GameState::getGame() const{
    return m_game;
}

//no Coin
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

//won state

void WonState::insertCoin(){
    
}
void WonState::pressButton(){
    
}
void WonState::moveStick(sf::Vector2i direction){
    
}
void WonState::update(sf::Time delta){
    
}
void WonState::draw(sf::RenderWindow& window){
    
}

//lost state
void LostState::insertCoin(){
    
}
void LostState::pressButton(){
    
}
void LostState::moveStick(sf::Vector2i direction){
    
}
void LostState::update(sf::Time delta){
    
}
void LostState::draw(sf::RenderWindow& window){
    
}

//playing state
void PlayingState::insertCoin(){
    
}
void PlayingState::pressButton(){
    
}
void PlayingState::moveStick(sf::Vector2i direction){
    
}
void PlayingState::update(sf::Time delta){
    
}
void PlayingState::draw(sf::RenderWindow& window){
    
}

//get ready state
void GetReadyState::insertCoin(){
    
}
void GetReadyState::pressButton(){
    
}
void GetReadyState::moveStick(sf::Vector2i direction){
    
}
void GetReadyState::update(sf::Time delta){
    
}
void GetReadyState::draw(sf::RenderWindow& window){
    
}
