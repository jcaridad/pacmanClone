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
    
    Maze();
    void loadLevel(string fileName);
    
private:
    
    enum cellData{
        Empty,
        Wall,
        Dot,
        SuperDot,
        Bonus
    };
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Vector2i m_mazeSize;
    std::vector<cellData> m_mazeData;
    
    sf::RenderTexture m_renderTexture;
};

#endif /* maze_hpp */
