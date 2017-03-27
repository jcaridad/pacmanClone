//
//  game.cpp
//  smflTest
//
//  Created by Jymar Caridad on 3/6/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#include "game.hpp"
#include <iostream>



using namespace std;

Game::Game()
:m_window(sf::VideoMode(448,576), "Pac Man SFML"){
    
    if(!m_gameFont.loadFromFile("/Users/jymarcaridad/ClassCodes/smflTest/smflTest/assets/font.ttf")){
        throw runtime_error("Unable to load the font file");
    }
    
    
    m_gameStates[GameState::noCoin] = new NoCoinState(this);
    m_gameStates[GameState::getReady] = new GetReadyState(this);
    m_gameStates[GameState::Playing] = new PlayingState(this);
    m_gameStates[GameState::Won] = new WonState(this);
    m_gameStates[GameState::Lost] = new LostState(this);
    
    changeGameState(GameState::noCoin);
}

Game::~Game(){
    for(GameState* gameState : m_gameStates){
        delete gameState;
    }
}

void Game::run(){
    while(m_window.isOpen()){
        sf::Event event;
        while(m_window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                m_window.close();
            }
            //keyboard inputs
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::I){
                    m_currentState->insertCoin();
                }
                if(event.key.code == sf::Keyboard::S){
                    m_currentState->pressButton();
                }
                if(event.key.code == sf::Keyboard::Left){
                    m_currentState->moveStick(sf::Vector2i(-1, 0));
                }
                if(event.key.code == sf::Keyboard::Right){
                    m_currentState->moveStick(sf::Vector2i(1, 0));
                }
                if(event.key.code == sf::Keyboard::Up){
                    m_currentState->moveStick(sf::Vector2i(0, -1));
                }
                if(event.key.code == sf::Keyboard::Down){
                    m_currentState->moveStick(sf::Vector2i(0, 1));
                }
            }
        }
        m_currentState->update(sf::seconds(1));
        m_window.clear();
        m_currentState->draw(m_window);
        m_window.display();
    }

}


void Game::changeGameState(GameState:: State gameState){
    m_currentState = m_gameStates[gameState];
}

