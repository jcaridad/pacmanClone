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

/**
 * Animator Class
 * This Class handles all the animation that is rendered in the game. Mainly used show P{layer and Ghost Animation
 */

class Animator{
public:
    
    /**
     *
     * Animator Constructor.
     * Intiates the following member functions
     * - m_currentFrame
     * - m_isPlaying
     * - m_duration
     * - m_loop
     */
    Animator();

    /**
     * This function stores animation frames clipped from the spritesheet
     *
     * @param a_frame an animation frame
     *
     */
    void addFrame(sf::IntRect a_frame);
    
    /**
     * This functions acts as a switch to play the sprite animation
     *
     * @param a_duration length of animation time
     * @param a_loop whether the animation should loop or not
     *
     */
    void play(sf::Time a_duration, bool a_loop);
    
    /**
     * This functions checks if the animation is playing
     *
     * @return Returns true if the animation is playing
     *
     */
    bool isPlaying() const;
    
    /**
     * This functions checks how long have the current animation frame have been playing and updates it to the new frame if the frame duration have elaposed
     *
     * @param a_delta current time
     *
     */
    void update(sf::Time a_delta);
    
    /**
     * This function specify which sprite to animate and set all the corresponding animation frames to the sprite passed into the function
     *
     * @param a_sprite the sprite that have to be animated 
     *
     */
    void animate(sf::Sprite& a_sprite);
    
private:
    /**
     * A private std::vector container
     * Holds all the animation frames
     */
    vector<sf::IntRect> m_frames;
    
    /**
     * A private variable
     * Indicates if the animation is playing or not
     */
    bool m_isPlaying;
    
    /**
     * A private variable.
     * Duration of the Animation
     */
    sf::Time m_duration;
    
    /**
     * A private variable.
     * Indicates if the animation should loop or not
     */
    bool m_loop;
    
    /**
     * A private variable.
     * Index of the current frame
     */
    unsigned int m_currentFrame;
};
#endif /* animator_hpp */
