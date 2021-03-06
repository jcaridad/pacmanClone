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

GameState::GameState(Game* a_game)
:m_game(a_game){
}

NoCoinState::NoCoinState(Game* a_game)
:GameState(a_game){
    m_logoSprite.setTexture(a_game->getLogo());
    m_logoSprite.setScale(.50, .50);
    m_logoSprite.setPosition(50, 50);
    
    m_text.setFont(a_game->getFont());
    m_text.setCharacterSize(15);
    m_text.setString("Press I to Insert Coin!");
    centerOrigin(m_text);
    m_text.setPosition(225, 150);
    
    m_displayText = true;
}

GetReadyState::GetReadyState(Game* a_game)
:GameState(a_game){
    m_text.setFont(a_game->getFont());
    m_text.setString("    Get Ready!\nPress S to Start!");
    m_text.setCharacterSize(14);
    
    centerOrigin(m_text);
    m_text.setPosition(225, 240);
}

WonState::WonState(Game* a_game, GameState* a_playingState)
:GameState(a_game)
,m_playingState(static_cast<PlayingState*>(a_playingState)){
    m_text.setFont(a_game->getFont());
    m_text.setString("You Won!");
    m_text.setCharacterSize(42);
    centerOrigin(m_text);
    m_text.setPosition(225, 240);
    
}
LostState::LostState(Game* a_game, GameState* a_playingState)
:GameState(a_game)
,m_playingState(static_cast<PlayingState*>(a_playingState)){
    m_text.setFont(a_game->getFont());
    m_text.setString("You Lost!");
    m_text.setCharacterSize(14);
    
    centerOrigin(m_text);
    m_text.setPosition(225, 220);
    
    m_countDownTxt.setFont(a_game->getFont());
    m_countDownTxt.setCharacterSize(12);
    
    centerOrigin(m_countDownTxt);
    m_countDownTxt.setPosition(70, 250);
    
    m_scoreDisplay.setFont(a_game->getFont());
    m_scoreDisplay.setCharacterSize(12);
    
    centerOrigin(m_scoreDisplay);
    m_scoreDisplay.setPosition(200, 300);
    
}
PlayingState::PlayingState(Game* a_game)
:GameState(a_game)
,m_maze(a_game->getTexture())
,m_bonus(a_game->getTexture())
,m_pacMan(nullptr)
,m_lvl(0)
,m_lives(3)
,m_score(0){

    //GAME
    m_pacMan = new Pacman(a_game->getTexture());
    m_pacMan->setMaze(&m_maze);
    m_pacMan->setPosition(m_maze.mapCellToPixel(m_maze.getPacManPosition()));
    
    for (auto ghostPosition : m_maze.getGhostPositions()){
        Ghost* ghost = new Ghost(a_game->getTexture(), m_pacMan);
        ghost->setMaze(&m_maze);
        ghost->setPosition(m_maze.mapCellToPixel(ghostPosition));
        m_ghosts.push_back(ghost);
    }
    
    gameOver();
    
    m_bonus.setPosition(-16, -16);
    
    
    //HUD
    m_scoreText.setFont(a_game->getFont());
    m_scoreText.setCharacterSize(10);
    m_scoreText.setPosition(5, 512);
    
    m_levelText.setFont(a_game->getFont());
    m_levelText.setCharacterSize(10);
    m_levelText.setPosition(165, 512);
    
    m_dotsLeft.setFont(a_game->getFont());
    m_dotsLeft.setCharacterSize(10);
    m_dotsLeft.setPosition(285, 512);
    
    for(auto& livesLeft : m_livesLeft){
        livesLeft.setTexture(a_game->getTexture());
        livesLeft.setTextureRect(sf::IntRect(122/2, 0, 10, 10));
    }
    
    m_livesLeft[0].setPosition(sf::Vector2f(415, 512));
    m_livesLeft[1].setPosition(sf::Vector2f(425, 512));
    m_livesLeft[2].setPosition(sf::Vector2f(435, 512));

}

PlayingState::~PlayingState(){
    delete m_pacMan;
    
    for(Ghost* ghost : m_ghosts){
        delete ghost;
    }
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
void NoCoinState::moveStick(sf::Vector2i a_direction){
    
}
void NoCoinState::update(sf::Time a_delta){
    static sf::Time timeBuffer = sf::Time::Zero;
    timeBuffer += a_delta;
    
    while(timeBuffer >= sf::seconds(0.5)){
        m_displayText = !m_displayText;
        timeBuffer -= sf::seconds(1);
    }
    
}
void NoCoinState::draw(sf::RenderWindow& a_window){
    a_window.draw(m_logoSprite);
    if(m_displayText){
        a_window.draw(m_text);
    }
}

//get ready state
void GetReadyState::insertCoin(){
    
}
void GetReadyState::pressButton(){
    getGame()->changeGameState(GameState::Playing);
}
void GetReadyState::moveStick(sf::Vector2i a_direction){

}
void GetReadyState::update(sf::Time a_delta){
    
}
void GetReadyState::draw(sf::RenderWindow& a_window){
    a_window.draw(m_text);
}

//won state

void WonState::insertCoin(){
    
}
void WonState::pressButton(){
    
}
void WonState::moveStick(sf::Vector2i a_direction){
    
}
void WonState::update(sf::Time a_delta){
    static sf::Time timeBuffer = sf::Time::Zero;
    
    timeBuffer += a_delta;
    
    if(timeBuffer.asSeconds() > 5){
        m_playingState->loadNextLvl();

        getGame()->changeGameState(GameState::getReady);
    }
}
void WonState::draw(sf::RenderWindow& a_window){
    a_window.draw(m_text);
}

//lost state
void LostState::insertCoin(){
    m_playingState->resetLives();
    
    getGame()->changeGameState(GameState::getReady);
}
void LostState::pressButton(){
    
}
void LostState::moveStick(sf::Vector2i a_direction){
    
}
void LostState::update(sf::Time a_delta){
    m_countDown += a_delta;
    
    if(m_countDown.asSeconds() >= 10){
        m_playingState->gameOver();
        getGame()->changeGameState(GameState::noCoin);
    }
    
    m_countDownTxt.setString("Insert Coin to Continue... "+ to_string(10 - static_cast<int>(m_countDown.asSeconds())));
    m_scoreDisplay.setString("Score: " + to_string(m_playingState->getScore()));
}
void LostState::draw(sf::RenderWindow& a_window){
    a_window.draw(m_text);
    a_window.draw(m_scoreDisplay);
    a_window.draw(m_countDownTxt);
}

//playing state
void PlayingState::insertCoin(){

}
void PlayingState::pressButton(){

}
void PlayingState::moveStick(sf::Vector2i a_direction){
    m_pacMan->setDirection(a_direction);
}
void PlayingState::update(sf::Time a_delta){
    m_pacMan->update(a_delta);
    
    for(Ghost* ghost : m_ghosts){
        ghost->update(a_delta);
    }
    
    //check collision player->dots, player-ghosts, player->weak ghosts
    //scores
    //  dot = 5
    //  super dot = 25
    //  weak ghost = 100
    //  bonus = 500
    
    sf::Vector2f pixelPosition = m_pacMan->getPosition();
    sf::Vector2f offset(fmod(pixelPosition.x, 16), fmod(pixelPosition.y, 16));
    
    offset-= sf::Vector2f(8,8);
    
    if (offset.x <= 2 && offset.x >= -2 && offset.y <= 2 && offset.y >= -2){
        sf::Vector2i cellPosition = m_maze.mapPixelToCell(pixelPosition);
        
        if (m_maze.isDot(cellPosition)){
            m_score += 5;
        }
        else if (m_maze.isSuperDot(cellPosition)){
            for (Ghost* ghost : m_ghosts){
                ghost->setWeak(sf::seconds(5));
            }
            
            m_score += 25;
        }
        m_maze.pickObject(cellPosition);
    }
    
    for (Ghost* ghost : m_ghosts){
        if (ghost->getCollision().intersects(m_pacMan->getCollision())){
            if (ghost->isWeak()){
                ghost->setWeak(sf::Time::Zero);
                ghost->setPosition(m_maze.mapCellToPixel(m_maze.getRespawnPosition()));
                m_score += 100;
            }
            else{
                m_pacMan->die();
            }
        }
    }
    
    if (m_pacMan->isDead()){
        m_pacMan->reset();
        
        m_lives--;
        
        if (m_lives < 0)
            getGame()->changeGameState(GameState::Lost);
        else
            resetCharacters();
    }
    
    if(m_bonus.getCollision().intersects(m_pacMan->getCollision())){
        m_bonus.setPosition(-16, -16);
        m_score += 500;
    }
    if(m_maze.getRemainingDots() == 0){
        getGame()->changeGameState(GameState::Won);
    }
    if(m_maze.getRemainingDots() == 150){
        m_bonus.setPosition(m_maze.mapCellToPixel(m_maze.getRespawnPosition()));

    }
    m_scoreText.setString(to_string(m_score));
    m_dotsLeft.setString(to_string(m_maze.getRemainingDots()) + "x dots");
    
}
void PlayingState::draw(sf::RenderWindow& a_window){
    a_window.clear();
    a_window.draw(m_maze);
    a_window.draw(m_bonus);
    a_window.draw(*m_pacMan);
    for(Ghost* ghost : m_ghosts){
        a_window.draw(*ghost);
    }
    
    
    a_window.draw(m_scoreText);
    a_window.draw(m_levelText);
    a_window.draw(m_dotsLeft);
    
    for(unsigned int i = 0; i < m_lives; i++){
        a_window.draw(m_livesLeft[i]);
    }
    
}

void PlayingState::resetCharacters(){
    m_pacMan->setPosition(m_maze.mapCellToPixel(m_maze.getPacManPosition()));
    
    auto ghostPositions = m_maze.getGhostPositions();
    for (unsigned int i = 0; i < m_ghosts.size(); i++){
        m_ghosts[i]->setPosition(m_maze.mapCellToPixel(ghostPositions[i]));
    }
    
}

void PlayingState::loadNextLvl(){
    
    m_lvl++;
    
    int mapLevel = m_lvl % 3;
    int speedLevel = floor(m_lvl / 3);
    
    if (mapLevel == 0){
        m_maze.loadLevel("original");
        m_bonus.setFruit(Bonus::Fruit::Cherry);
    }
    else if (mapLevel == 1){
        m_maze.loadLevel("msPacMan");
        m_bonus.setFruit(Bonus::Fruit::Banana);
    }
    else if	(mapLevel == 2){
        m_maze.loadLevel("prototype");
        m_bonus.setFruit(Bonus::Fruit::Apple);
    }
    
    // Destroy previous characters
    for (Ghost* ghost : m_ghosts)
        delete ghost;
    
    m_ghosts.clear();
    
    // Create new characters
    for (auto ghostPosition : m_maze.getGhostPositions()){
        Ghost* ghost = new Ghost(getGame()->getTexture(), m_pacMan);
        ghost->setMaze(&m_maze);
        //ghost->setPosition(m_maze.mapCellToPixel(ghostPosition));
        m_ghosts.push_back(ghost);
    }
    
    // Change speed according to the new level
    float speed = 50 + (speedLevel * 50);
    
    m_pacMan->setSpeed(speed + 25);
    
    for (auto& ghost : m_ghosts){
        ghost->setSpeed(speed);
    }
    
    resetCharacters();
    
    //Update level text
    m_levelText.setString("level " + std::to_string(speedLevel) + " - " + std::to_string(mapLevel+1));
    
}

void PlayingState::gameOver(){
    resetLives();
    
    m_lvl = 0;
    resetCurrentLvl();
    
    m_score = 0;
}

void PlayingState::resetLives(){
    m_lives = 3;
}

void PlayingState::resetCurrentLvl(){
    m_lvl--;
    loadNextLvl();
}

int PlayingState::getScore(){
    return m_score;
}
