//
//  bonus.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef bonus_hpp
#define bonus_hpp

#include <stdio.h>
#include "character.hpp"

#include <SFML/Graphics.hpp>

/**
 * Bonus Class
 * This class inherits from the Character Class. It renders the fruit bonuses depending on what stage and map the game is currently on.
 */
class Bonus : public Character{
    
public:
    /**
     * An enum type
     * Type of fruits that can be rendered
     */
    enum Fruit{
        Cherry,
        Apple,
        Banana
    };
    
    /**
     * A Bonus Constructor
     * Initates m_visual variable
     * Also sets the default fruit as Apple
     */
    Bonus(sf::Texture& a_Texture);
    
    /**
     * This function sets what fruit to be rendered on the screen
     *
     * @param a_fruit the fruit instance to be set on screen
     */
    void setFruit(Fruit a_fruit);
    
private:
    /**
     * A private sf::Sprite variable
     * The sprite that is shown on the screen
     * @see sf::Sprite: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php
     */
    sf::Sprite m_visual;
    
    /**
     * This private function renders the current animated sprite into the map
     *
     * @param a_target the render window instance
     * @param a_states the state that the sf::RenderTarget Instance is in
     */
    void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;
    
};
#endif /* bonus_hpp */
