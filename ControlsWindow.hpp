#ifndef __CONTROLS_WINDOW_HPP__
#define __CONTROLS_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"

// Class that contains a window that displays the controls
// for a character
class ControlsWindow
{
    private:
        // Window in which everything is shown (it's a pointer
        // because the window lives in the main function, we are
        // just going to store a reference to it)
        sf::RenderWindow * window;

        // Sprite for the image that contains the controls
        sf::Sprite controlsSprite;

        // Glitch sound that plays when the controls window is initialized
        sf::Sound glitchSound;

    public:
        ControlsWindow(sf::RenderWindow * window, TextureHolder& textureHolder, SoundHolder& soundHolder);
        void run();
};

#endif // __CONTROLS_WINDOW_HPP__
