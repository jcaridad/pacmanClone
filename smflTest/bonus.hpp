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

#include <SFML/Graphics.hpp>

class Bonus : public sf::Drawable, public sf::Transformable{
    
public:
    
    enum Fruit{
        Cherry,
        Apple,
        Orange
    };
    
    Bonus(sf::Texture& Texture);
    void setFruit(Fruit fruit);
    
private:
    sf::Sprite m_visual;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};
#endif /* bonus_hpp */
