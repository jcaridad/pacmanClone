//
//  dot.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef dot_hpp
#define dot_hpp

#include <SFML/Graphics.hpp>

/**
 * This function renders the dot for the game
 *
 * @return returns the dot created
 * @see sf::CircleShape: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1CircleShape.php
 */
sf::CircleShape getDot();


/**
 * This function renders the super dot for the game
 *
 * @return returns the super dot created
 * @see sf::CircleShape: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1CircleShape.php
 */
sf::CircleShape getSuperDot();


#endif /* dot_hpp */
