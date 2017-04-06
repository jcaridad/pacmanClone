//
//  gameState.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/6/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef gameState_hpp
#define gameState_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "pacman.hpp"
#include "ghost.hpp"
#include "maze.hpp"

class Game;

class GameState{
public:
    enum State{
        noCoin,
        getReady,
        Playing,
        Won,
        Lost,
        Count
    };

    GameState (Game* game);
    Game* getGame() const;
    
    
    virtual void insertCoin() = 0;
    virtual void pressButton() = 0;
    virtual void moveStick(sf::Vector2i direction) = 0;
    //virtual void handleInput() = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    
private:
    Game* m_game;
};


class NoCoinState : public GameState{
public:
    NoCoinState(Game* game);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);

private:
    sf::Text m_text;
    sf::Sprite m_logoSprite;
    
    bool m_displayText;
};

class GetReadyState : public GameState{
public:
    GetReadyState(Game* game);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Text m_text;
};

class WonState : public GameState{
public:
    WonState(Game* game);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Text m_text;
    
};

class LostState : public GameState{
public:
    LostState(Game* game);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Text m_text;
    sf::Time m_countDown;
    sf::Text m_countDownTxt;
    
};

class PlayingState : public GameState{
public:
    PlayingState(Game* game);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    Pacman* m_pacMan;
    vector<Ghost*> m_ghosts;
    //Ghost m_ghost;
    Maze m_maze;
};


#endif /* gameState_hpp */
