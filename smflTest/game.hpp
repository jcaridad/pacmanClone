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

using namespace std;
/**
 * Game Class
 * This Class is the center of the whole game. The game states are intiated and runs through this class. The game assets are also loaded from here.
 */
class Game{
public:
    /**
     * A Game Constuctor
     * Initates m_window variable to a 448 x 528 pixel screen
     * Also loads up game assets and sets up all the game states.
     */
    Game();
    /**
     * A Game Destructor
     */
    ~Game();
    
    /**
     * This function fires up the game. Game time, Key Inputs and window rendering all run through this function
     */
    void run();
    
    /**
     * This is a get function for m_gameFont
     *
     * @return returns the game font that was loaded
     */
    sf::Font& getFont();
    
    /**
     * This is a get function for m_gameLogo
     *
     * @return returns the game logo that was loaded
     */
    sf::Texture& getLogo();
    
    /**
     * This is a get function for m_gameTexture
     *
     * @return returns the game sprite sheet that was loaded
     */
    sf::Texture& getTexture();
    
    /**
     * This function changes the current game state
     *
     * @param a_gameState the gamestate to replace the current one
     */
    void changeGameState(GameState::State a_gameState);
    
private:
    /**
     * A private sf::RenderWindow variable
     * The game window
     * @see sf::RenderWindow: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php
     */
    sf::RenderWindow m_window;
    
    /**
     * A private GameState instance
     * The current state the game is in
     */
    GameState* m_currentState;
    
    /**
     * A private std::array container
     * Holds all the game state instances
     */
    array<GameState*, GameState::Count> m_gameStates;
    
    /**
     * A private sf::Font variable
     * Font of used in the game
     * @see sf::Font: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Font.php
     */
    sf::Font m_gameFont;
    
    /**
     * A private sf::Texture variable
     * The game logo
          * @see sf::Texture: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Texture.php
     */
    sf::Texture m_gameLogo;
    
    /**
     * A private sf::Texture variable
     * The game sprite sheet
     * @see sf::Texture: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Texture.php
     */
    sf::Texture m_gameSprites;
};

#endif /* game_hpp */
