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
#include "bonus.hpp"
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
    GetReadyState(Game* game, GameState* playingState);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Text m_text;
    GameState* m_playingState;
};

class PlayingState : public GameState{
public:
    PlayingState(Game* game);
    ~PlayingState();
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
    void loadNextLvl();
    void gameOver();
    void resetLives();
    void resetCurrentLvl();
    
    void resetCharacters();
    
    int getScore();
    
private:
    Pacman* m_pacMan;
    vector<Ghost*> m_ghosts;
    Maze m_maze;
    Bonus m_bonus;
    sf::RenderTexture m_gameScene;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Text m_dotsLeft;
    sf::Sprite m_livesLeft[3];
    
    int m_lvl;
    int m_lives;
    int m_score;
};

class WonState : public GameState{
public:
    WonState(Game* game, GameState* playingState);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Text m_text;
    
    PlayingState* m_playingState;
    
};

class LostState : public GameState{
public:
    LostState(Game* game, GameState* playingState);
    void insertCoin();
    void pressButton();
    void moveStick(sf::Vector2i direction);
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Text m_text;
    sf::Time m_countDown;
    sf::Text m_countDownTxt;
    sf::Text m_scoreDisplay;
    
    PlayingState* m_playingState;
};
#endif /* gameState_hpp */
