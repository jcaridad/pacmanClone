//
//  game.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/6/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#include "gameState.hpp"

class Game{
public:

    Game();
    ~Game();
    
    void run();
    
    sf::Font& getFont();
    sf::Texture& getLogo();
    sf::Texture& getTexture();
    
    void changeGameState(GameState::State a_gameState);


private:
    sf::RenderWindow m_window;
    GameState* m_currentState;
    std::array<GameState*, GameState::Count> m_gameStates;
    
    sf::Font m_gameFont;
    sf::Texture m_gameLogo;
    sf::Texture m_gameSprites;
};

#endif /* game_hpp */
