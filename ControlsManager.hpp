#ifndef __CONTROLS_WINDOW_HPP__
#define __CONTROLS_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include <map>

// Class that manages everything related to controls
class ControlsManager
{
    private:
        // Window in which the controls are shown (it's a pointer
        // because the window lives in the main function, we are
        // just going to store a reference to it)
        sf::RenderWindow * window;

        // Sprite for the image that contains the controls
        sf::Sprite controlsSprite;

        // Glitch sound that plays when the controls window is initialized
        sf::Sound glitchSound;

        // Map that stores, for each character, the control it uses
        std::map<CharName, Control> characterControls;

        // Function that indicates if a control is free (not used by a character)
        bool isAvailable(Control c);

    public:
        ControlsManager(sf::RenderWindow * window, TextureHolder& textureHolder, SoundHolder& soundHolder);
        void showControls(CharName character);
};

#endif // __CONTROLS_WINDOW_HPP__
