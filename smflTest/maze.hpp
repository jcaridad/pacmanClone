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
    
    Maze(sf::Texture& texture);
    void loadLevel(string fileName);
    sf::Vector2i getSize() const;
    sf::Vector2i getPacManPosition() const;
    vector<sf::Vector2i> getGhostPositions() const;
    
    inline size_t positionToIndex(sf::Vector2i position) const;
    inline sf::Vector2i indexToPosition(size_t index) const;
    
    sf::Vector2i mapPixelToCell(sf::Vector2f pixel) const;
    sf::Vector2f mapCellToPixel(sf::Vector2i cell) const;
    
    bool isWall(sf::Vector2i position) const;
    bool isTunnel(sf::Vector2i position) const;
private:
    
    enum cellData{
        Empty,
        Wall,
        Dot,
        SuperDot,
        Tunnel,
        Bonus
    };
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Vector2i m_mazeSize;
    vector<cellData> m_mazeData;
    sf::Vector2i m_pacManPosition;
    vector<sf::Vector2i> m_ghostPositions;
    sf::RenderTexture m_renderTexture;
    
    sf::Texture& m_texture;
};

#endif /* maze_hpp */
