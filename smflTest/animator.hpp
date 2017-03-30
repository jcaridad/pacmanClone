//
//  animator.hpp
//  smflTest
//
//  Created by Jymar Caridad on 3/27/17.
//  Copyright © 2017 jcaridad. All rights reserved.
//

#ifndef animator_hpp
#define animator_hpp

#include <SFML/Graphics.hpp>

using namespace std;

class Animator{
public:
    Animator();
    
    void addFrame(sf::IntRect frame);
    
    void play(sf::Time duration, bool loop);
    bool isPlaying() const;
    
    void update(sf::Time delta);
    void animate(sf::Sprite& sprite);
    
private:
    vector<sf::IntRect> m_frames;
    
    bool m_isPlaying;
    sf::Time m_duration;
    bool m_loop;
    
    unsigned int m_currentFrame;
};
#endif /* animator_hpp */
