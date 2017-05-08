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
/**
 * Maze Class
 * This Inherits from sf::Drawable. It has all the maze methods are handled in this class. The way that the map data are uploaded and stored can be seen here.
 */
class Maze : public sf::Drawable{
public:
    /**
     * A Maze Consturctor
     * Initiates the following member variables
     * -m_mazeSize
     * -m_texture
     */
    Maze(sf::Texture& a_texture);
    
    /**
     * This function reads a 28 x 31 image(PNG) which represent the map, then read the pixel data and translate into a vector of sf::Vector2i.
     * Each color in the image represent certain maze entity. Black are Walls, White are the pellets, Green are the super pellets, Red are the ghost spawn point, Blue is Pac-Man/QuackMan's spawn point, and Magenta is the ghost respawn point.
     * This function also takes the maze data and renders wall sprites according to its position (Outer Corner, Inner Corner, Border).
     * @param a_fileName the map image file name
     */
    void loadLevel(string a_fileName);
    
    /**
     * This function is a get function for m_mazeSize
     *
     * @return returns the size of the map
     */
    sf::Vector2i getSize() const;
    
    /**
     * This function is a get funciton for m_pacmanPosition
     *
     * @return returns the position of Pac-Man/QuackMan in the maze
     */
    sf::Vector2i getPacManPosition() const;
    
    /**
     * This funciton is a get function for m_ghostPositions
     *
     * @return returns the vector of the positions of ghost in the maze
     */
    vector<sf::Vector2i> getGhostPositions() const;
    
    /**
     * This function is a get function for m_respawnPosition
     *
     * @return returns the respawn position
     */
    sf::Vector2i getRespawnPosition() const;
    
    /**
     * This function converts the pixel position into the corresponding maze data
     *
     * @param a_position The pixel position
     * @return returns the maze data that matches the position
     */
    inline size_t positionToIndex(sf::Vector2i a_position) const;
    
    /**
     * This function converts the maze data into the corresponding pixel position in the map
     *
     * @param a_index The maze data
     * @return returns the pixel position where the maze data is
     */
    inline sf::Vector2i indexToPosition(size_t a_index) const;
    
    /**
     * This function converts a pixel value into a cell value
     *
     * @param a_pixel the pixel value
     * @return returns the cell value that equates to the pixel value
     */
    sf::Vector2i mapPixelToCell(sf::Vector2f a_pixel) const;
    
    /**
     * This function converts a cell value into a pixel value
     *
     * @param a_cell the cell value
     * @return returns the pixel value that equates to the cell value
     */
    sf::Vector2f mapCellToPixel(sf::Vector2i a_cell) const;
    
    /**
     * This function checks if a wall is on the certain position
     *
     * @param a_position the position to be checked
     * @return returns true if a wall is on that position
     */
    bool isWall(sf::Vector2i a_position) const;
    
    /**
     * This function checks if a dot/pellet is on the certain position
     *
     * @param a_position the position to be checked
     * @return returns true if a dot/pellet is on that position
     */
    bool isDot(sf::Vector2i a_position) const;
    
    /**
     * This function checks if a super dot/pellet is on the certain position
     *
     * @param a_position the position to be checked
     * @return returns true if a super dot/pellet is on that position
     */
    bool isSuperDot(sf::Vector2i a_position) const;
    
    /**
     * This function checks if a bonus is on the certain position
     *
     * @param a_position the position to be checked
     * @return returns true if a bonus is on that position
     */
    bool isBonus(sf::Vector2i a_position) const;
    
    /**
     * This function sets the dot, super dot, and bonus as Empty in the maze data after collision, and also make sures that it does not set the walls to empty after collition
     *
     * @param a_position the position where the player is
     */
    void pickObject(sf::Vector2i a_position);
    
    /**
     * This function is a checks how many dots are left inside the maze
     *
     * @return returns the number of dots left in the maze
     */
    int getRemainingDots() const;
    
private:
    /**
     * An enum Type
     * The types of maze data
     */
    enum cellData{
        Empty,
        Wall,
        Dot,
        SuperDot,
        Bonus
    };
    
    /**
     * This private function renders the current animated sprite into the map
     *
     * @param a_target the render window instance
     * @param a_states the state that the sf::RenderTarget Instance is in
     */
    void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;
    
    /**
     * A private sf::Vector2i variable
     * Holds the size of the maze
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    sf::Vector2i m_mazeSize;
    
    /**
     * A private std::vector container
     * Holds all the maze data
     
     */
    vector<cellData> m_mazeData;
    
    /**
     * A private sf::Vector2i variable
     * Pac-Man/QuackMan's location in the map
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    sf::Vector2i m_pacManPosition;
    
    /**
     * A private std::vector container
     * Holds locations all the ghosts on the map
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    vector<sf::Vector2i> m_ghostPositions;
    
    /**
     * A private sf::Vector2i variable
     * Ghost respawn location in the map
     * @see sf::Vector2i: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
     */
    sf::Vector2i m_respawnPosition;
    
    /**
     * A private sf::RenderTexture varuable
     * The texture of the maze that is rendered to the screen
     */
    sf::RenderTexture m_renderTexture;
    
    /**
     * A private sf::Texture variable
     * The texture instance for the game
     * @see sf::Texture: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Texture.php
     */
    sf::Texture& m_texture;
};

#endif /* maze_hpp */
