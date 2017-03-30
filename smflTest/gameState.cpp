//
//  gameState.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/6/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "gameState.hpp"
#include "game.hpp"

using namespace std;


template <typename T>
void centerOrigin(T& drawable)
{
    sf::FloatRect bound = drawable.getLocalBounds();
    drawable.setOrigin(bound.width/2, bound.height/2);
}

GameState::GameState(Game* game)
:m_game(game){
}

NoCoinState::NoCoinState(Game* game)
:GameState(game){
    m_logoSprite.setTexture(game->getLogo());
    m_logoSprite.setScale(.50, .50);
    m_logoSprite.setPosition(40, 50);
    
    m_text.setFont(game->getFont());
    m_text.setCharacterSize(15);
    m_text.setString("Press I to Insert Coin!");
    centerOrigin(m_text);
    m_text.setPosition(225, 150);
    
    m_displayText = true;
}

GetReadyState::GetReadyState(Game* game)
:GameState(game){
    m_text.setFont(game->getFont());
    m_text.setString("    Get Ready!\nPress S to Start!");
    m_text.setCharacterSize(14);
    
    centerOrigin(m_text);
    m_text.setPosition(225, 240);
}

WonState::WonState(Game* game)
:GameState(game){
    m_text.setFont(game->getFont());
    m_text.setString("You Won!");
    m_text.setCharacterSize(42);
    centerOrigin(m_text);
    m_text.setPosition(225, 240);
    
}
LostState::LostState(Game* game)
:GameState(game){
    m_text.setFont(game->getFont());
    m_text.setString("You Lost!");
    m_text.setCharacterSize(14);
    
    centerOrigin(m_text);
    m_text.setPosition(225, 220);
    
    m_countDownTxt.setFont(game->getFont());
    m_countDownTxt.setCharacterSize(12);
    
    centerOrigin(m_countDownTxt);
    m_countDownTxt.setPosition(70, 250);
    
}
PlayingState::PlayingState(Game* game)
:GameState(game)
,m_pacMan(game->getTexture())
,m_ghost(game->getTexture()){
    m_pacMan.move(100,200);
    m_ghost.move(200,200);
}

Game * GameState::getGame() const{
    return m_game;
}

//no Coin
void NoCoinState::insertCoin(){
    getGame()->changeGameState(GameState::getReady);
}
void NoCoinState::pressButton(){
    
}
void NoCoinState::moveStick(sf::Vector2i direction){
    
}
void NoCoinState::update(sf::Time delta){
    static sf::Time timeBuffer = sf::Time::Zero;
    timeBuffer += delta;
    
    while(timeBuffer >= sf::seconds(0.5)){
        m_displayText = !m_displayText;
        timeBuffer -= sf::seconds(1);
    }
    
}
void NoCoinState::draw(sf::RenderWindow& window){
    window.draw(m_logoSprite);
    if(m_displayText){
        window.draw(m_text);
    }
}


//get ready state
void GetReadyState::insertCoin(){
    
}
void GetReadyState::pressButton(){
    getGame()->changeGameState(GameState::Playing);
}
void GetReadyState::moveStick(sf::Vector2i direction){
    if(direction.x == -1){
        getGame()->changeGameState(GameState::Lost);
    }
    else if(direction.x == 1){
        getGame()->changeGameState(GameState::Won);
    }
}
void GetReadyState::update(sf::Time delta){
    
}
void GetReadyState::draw(sf::RenderWindow& window){
    window.draw(m_text);
}

//won state

void WonState::insertCoin(){
    
}
void WonState::pressButton(){
    
}
void WonState::moveStick(sf::Vector2i direction){
    
}
void WonState::update(sf::Time delta){
    static sf::Time timeBuffer = sf::Time::Zero;
    
    timeBuffer += delta;
    
    if(timeBuffer.asSeconds() > 5){
        getGame()->changeGameState(GameState::getReady);
    }
}
void WonState::draw(sf::RenderWindow& window){
    window.draw(m_text);
}

//lost state
void LostState::insertCoin(){
    
}
void LostState::pressButton(){
    
}
void LostState::moveStick(sf::Vector2i direction){
    
}
void LostState::update(sf::Time delta){
    m_countDown += delta;
    
    if(m_countDown.asSeconds() >= 10){
        getGame()->changeGameState(GameState::noCoin);
    }
    
    m_countDownTxt.setString("Insert Coin to Continue... "+ to_string(10 - static_cast<int>(m_countDown.asSeconds())));
}
void LostState::draw(sf::RenderWindow& window){
    window.draw(m_text);
    window.draw(m_countDownTxt);
}

//playing state
void PlayingState::insertCoin(){
    m_pacMan.die();
}
void PlayingState::pressButton(){
    m_ghost.setWeak(sf::seconds(3));
}
void PlayingState::moveStick(sf::Vector2i direction){
    
}
void PlayingState::update(sf::Time delta){
    m_pacMan.update(delta);
    m_ghost.update(delta);
}
void PlayingState::draw(sf::RenderWindow& window){
    window.draw(m_pacMan);
    window.draw(m_ghost);
}

