//
//  character.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/22/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include <SFML/Graphics.hpp>

class Character: public sf::Drawable, public sf::Transformable{
  
public:
    Character();
    
    void setSpeed(float speed);
    float getSpeed() const;
    
private:
    float m_speed;
    
};



#endif /* character_hpp */
