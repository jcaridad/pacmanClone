//
//  maze.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/29/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp

#include <array>
#include <SFML/Graphics.hpp>

using namespace std;

class Maze : public sf::Drawable{
public:
    
    Maze(sf::Texture& a_texture);
    void loadLevel(string a_fileName);
    sf::Vector2i getSize() const;
    sf::Vector2i getPacManPosition() const;
    vector<sf::Vector2i> getGhostPositions() const;
    sf::Vector2i getRespawnPosition() const;
    inline size_t positionToIndex(sf::Vector2i a_position) const;
    inline sf::Vector2i indexToPosition(size_t a_index) const;
    
    sf::Vector2i mapPixelToCell(sf::Vector2f a_pixel) const;
    sf::Vector2f mapCellToPixel(sf::Vector2i a_cell) const;
    
    bool isWall(sf::Vector2i a_position) const;
    bool isDot(sf::Vector2i a_position) const;
    bool isSuperDot(sf::Vector2i a_position) const;
    bool isBonus(sf::Vector2i a_position) const;
    
    void pickObject(sf::Vector2i a_position);
    
    int getRemainingDots() const; 
private:
    
    enum cellData{
        Empty,
        Wall,
        Dot,
        SuperDot,
        Bonus
    };
    void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;
    
    sf::Vector2i m_mazeSize;
    vector<cellData> m_mazeData;
    sf::Vector2i m_pacManPosition;
    vector<sf::Vector2i> m_ghostPositions;
    sf::Vector2i m_respawnPosition;
    sf::RenderTexture m_renderTexture;
    
    sf::Texture& m_texture;
};

#endif /* maze_hpp */
