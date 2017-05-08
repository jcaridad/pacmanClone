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
/**
 * GameState Class
 * Parent class to NoCoinState, GetReadyState, LostState, WonState, and Playing State. This is where the GameState loops circulates. Every GameState renders its own window and calls the next appropriate game state. This is also know as a Finite State Machine Pattern.
 */
class GameState{
public:
    /**
     * An enum type
     * The different game states
     */
    enum State{
        noCoin,
        getReady,
        Playing,
        Won,
        Lost,
        Count
    };

    /**
     * A GameState Constructor
     * Initiates an instance of the game, and the same game instance will be used for the five different game states
     * @param a_game the current game instance
     */
    GameState (Game* a_game);
    
    /**
     * This function is a get function for m_game
     *
     * @return returns the current game instance
     */
    Game* getGame() const;
    
    /**
     * A pure virtual function
     */
    virtual void insertCoin() = 0;
    
    /**
     * A pure virtual function
     */
    virtual void pressButton() = 0;
    
    /**
     * A pure virtual function
     *
     * @param a_direction the desired direction
     */
    virtual void moveStick(sf::Vector2i a_direction) = 0;
    
    /**
     * A pure virtual function
     *
     * @param delta the current time
     */
    virtual void update(sf::Time delta) = 0;
    
    /**
     * A pure virtual function
     *
     * @param a_window the window where the game is rendered
     */
    virtual void draw(sf::RenderWindow& a_window) = 0;
    
private:
    /**
     * A private Game instance
     * The current game being played
     */
    Game* m_game;
};

/**
 * NoCoinState Class
 * This class inherits from the GameState Class. This game state activates when the game is first launches and also when the player chooses not to continue.
 */
class NoCoinState : public GameState{
public:
    /**
     * A NoCoinState Constructor
     * Intiates the game logo, font, and the texts to be rendered on the screen
     * @param a_game the current game instance
     */
    NoCoinState(Game* a_game);
    
    /**
     * This function changes the current game's state to the get ready state
     * @see GameState Class
     */
    void insertCoin();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void pressButton();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     * @param a_direction the desired direction
     */
    void moveStick(sf::Vector2i a_direction);
    
    /**
     * This function updates the window which renders the game logo and the blinking "insert coin" text
     *
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
    /**
     * This function renders game logo and renders the text only if m_displayText is true which gives the blinking effect
     *
     * @param a_window the window where the game is rendered
     */
    void draw(sf::RenderWindow& a_window);

private:
    /**
     * A private sf::Text variable
     * The "insert coin" text
     */
    sf::Text m_text;
    
    /**
     * A private sf::Sprite variable
     * The game logo
     */
    sf::Sprite m_logoSprite;
    
    /**
     * A private boolean variable
     * Indicates whether the text should be rendered or not
     */
    bool m_displayText;
};

/**
 * GetReadyState
 * This class inherits from the GameState Class. This game state is launched right before the game is played. During the state it waits for an input("S") to ensure that the player is ready to play.
 */
class GetReadyState : public GameState{
public:
    /**
     * A GetReadyState Consturctor
     * Initiates the "Press S to Start" text to be rendered to the screen
     * @param a_game the current game instance
     */
    GetReadyState(Game* a_game);
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void insertCoin();
    
    /**
     * This function waits for the "S" input and switches the game state to the playing state
     */
    void pressButton();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     * @param a_direction the desired direction
     */
    void moveStick(sf::Vector2i a_direction);
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
    /**
     * This function renders the text on the window
     *
     * @param a_window the window where the game is rendered
     */
    void draw(sf::RenderWindow& a_window);
    
private:
    /**
     * A private sf::Text variable
     * The "press S to start" text
     */
    sf::Text m_text;
};

/**
 * Playing State Class
 * This class inherits from the GameState Class. This game state is where everything is implemented. The game is played in this state. It takes care of loading the levels, calculating scores, checking for Player VS Ghost Collisions, picking up pellets, and rendering the HUD.
 */
class PlayingState : public GameState{
public:
    /**
     * A PlayingState Constructor
     * Intiates the following member variables
     * - m_maze
     * - m_bonus
     * - m_pacMan
     * - m_lvl
     * - m_lives
     * - m_score
     * Also sets up everything on the maze and prepares all the HUD elements to be rendered to the screen
     * @param the current game instance
     */
    PlayingState(Game* a_game);
    
    /**
     * A PlayingState Destructor
     * Deletes the current instances of Pac-Man/QuackMan and ghosts
     */
    ~PlayingState();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void insertCoin();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void pressButton();
    
    /**
     * This function sets the direction where Pac-Man/QuackMan is going
     *
     * @param a_direction the desired direction
     */
    void moveStick(sf::Vector2i a_direction);
    
    /**
     * This function does two major things: Score Counting and Collision Checking
     * Collision Checking: It checks if the player collided with "strong" ghosts, "weak" ghosts, dots, super dots, or a bonus. If the player collided with a "strong" ghost then the player loses a life and all the character entities resets to its original position. If the player collides with anything else it earns scores
     * Score Counting: The player earns score depending on what it collides with or "eats". Dots are 5 pts, SuperDots are 25 pts, "Weak" Ghosts are 100 pts, and the bonus, which shows up when there are only 150 dots left in the maze, is 500 pts
     *
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
    /**
     * This functions draws everything on the screen. The Maze, Pac-Man/QuackMan, The ghosts, and the HUD
     *
     * @param a_window the window where the game is rendered
     */
    void draw(sf::RenderWindow& a_window);
    
    /**
     * This function the levels and changes the game difficulty. There are 3 different maps that can be played and the speeds increases everytime the 3 maps are completed.
     */
    void loadNextLvl();
    
    /**
     * This function resets all the in game variables. Set everything like a new game
     */
    void gameOver();
    
    /**
     * This function resets the just the number of lives back to 3. Used when a player decideds to continue after losing.
     */
    void resetLives();
    
    /**
     * This function resets the current level back to its original status, meaning all dots, superDots and Bonus is there
     */
    void resetCurrentLvl();
    
    /**
     * This function resets all the character entities back to its original spawn points
     */
    void resetCharacters();
    
    /**
     * This is a get function for m_score;
     *
     * @return returns the current game score
     */
    int getScore();
    
private:
    
    /**
     * A private Pacman instance
     * The current player entity
     */
    Pacman* m_pacMan;
    
    /**
     * A private std::vector container
     * Holds all the ghost entites
     */
    vector<Ghost*> m_ghosts;
    
    /**
     * A private Maze instance
     * The current maze
     */
    Maze m_maze;
    
    /**
     * A private Bonus instance
     * The current bonus
     */
    Bonus m_bonus;
    
    /**
     * A private sf::Text variable
     * The score text
     */
    sf::Text m_scoreText;
    
    /**
     * A private sf::Text variable
     * The level text
     */
    sf::Text m_levelText;
    
    /**
     * A private sf::Text variable
     * The dots left text
     */
    sf::Text m_dotsLeft;
    
    /**
     * A private sf::Sprite variable
     * The number of lives left display
     */
    sf::Sprite m_livesLeft[3];
    
    /**
     * A private integer variable
     * The level number (0 = original, 1 = msPacMan, 2 = custom)
     */
    int m_lvl;
    
    /**
     * A private integer variable
     * The number of lives
     */
    int m_lives;
    
    /**
     * A private integer variable
     * The current score
     */
    int m_score;
};

/**
 * WonState Class
 * This Class inherits from the GameState Class. This game state announces that the play have complete the map. After 5 seconds the next game will start.
 */
class WonState : public GameState{
public:
    /**
     * A WonState Constructor
     * Intiates the text to be rendered on the screen and make sures that the scores and the number of lives are passed to the next level properly
     * @param a_game the current game instance
     * @param a_playingState the current playingState entity
     */
    WonState(Game* a_game, GameState* a_playingState);
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void insertCoin();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void pressButton();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     * @param the desired direction
     */
    void moveStick(sf::Vector2i a_direction);
    
    /**
     * This function switches the current game state to the get ready state to play the next level after 5 seconds. Also loads the next level before switching to the next game state.
     *
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
    /**
     * This function renders the text to the screen
     *
     * @param a_window the window where the game is rendered
     */
    void draw(sf::RenderWindow& a_window);
    
private:
    /**
     * A private sf::Text variable
     * The "You Won!" text
     */
    sf::Text m_text;
    
    /**
     * A private PlayingState entity
     * Holds the current score and life count
     */
    PlayingState* m_playingState;
    
};

/**
 * LostState Class
 * This Class inherits from the GameState Class. This state announces that the player lost the game and is given an option to continue for 10 seconds. If the player chooses to continue, it will give the player another set of lives to play and continue where they left off. If the player chooses to let the timer go down to zero, the game will reset from scratch all the way back to the no coin state.
 */
class LostState : public GameState{
public:
    /**
     * A LostState Constructor
     * Intiates the text to be rendered on the screen and make sures that the score and the maze is kept just incase the player decides to continue
     * @param a_game the current game instance
     * @param a_playingState the current playingState entity
     */
    LostState(Game* a_game, GameState* a_playingState);
    
    /**
     * This function waits for the player to "insert a coin" and reset the number of lives and resume the current game being played
     */
    void insertCoin();
    
    /**
     * This is an empty function to override it's virtual counter part
     * @see GameState Class
     */
    void pressButton();
    
    /**
     * This function sets the direction where Pac-Man/QuackMan is going
     *
     * @param a_direction the desired direction
     */
    void moveStick(sf::Vector2i a_direction);
    
    
    /**
     * This funciton sets a countdown of 10 seconds the shows it to the screen and if the player does not insert a coin within the countdown then it declares Game Over and the game will reset from scratch and go back to the No Coin State
     *
     * @param a_delta the current time
     */
    void update(sf::Time a_delta);
    
    /**
     * This function renders the text to the screen
     *
     * @param a_window the window where the game is rendered
     */
    void draw(sf::RenderWindow& a_window);
    
private:
    /**
     * A private sf::Text variable
     * The "You Lost" Text
     */
    sf::Text m_text;
    
    /**
     * A private sf::Time variable
     * The countdown clock
     */
    sf::Time m_countDown;
    
    /**
     * A private sf::Text variable
     * The countdown text
     */
    sf::Text m_countDownTxt;
    
    /**
     * A private sf::Text variable
     * The current score text
     */
    sf::Text m_scoreDisplay;
    
    /**
     * A private PlayingState instance
     * Holds the current score, and the current maze data
     */
    PlayingState* m_playingState;
};
#endif /* gameState_hpp */
