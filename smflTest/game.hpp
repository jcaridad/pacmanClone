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


#include "gameState.hpp"

class Game{
public:

    Game();
    
    void run();
    
    void changeGameState(GameState::State gameState);
private:
    sf::RenderWindow m_window;
    GameState* m_currentState;
};

#endif /* game_hpp */
