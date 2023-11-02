#ifndef __WARNING_WINDOW_HPP__
#define __WARNING_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "MusicPlayer.hpp"

// Class for the warning window that appears at the beginning
class WarningWindow
{
    private:
        // Window in which everything is shown (it's a pointer
        // because the window lives in the main function, we are
        // just going to store a reference to it)
        sf::RenderWindow * window;

        // Sprite for the background that shows "warning" a lot
        // of times
        sf::Sprite backgroundSprite;

        // Sprite for the big text that appears saying "WARNING"
        sf::Sprite warningTitleSprite;

        // Sprite for the normal text that appears under the "WARNING" title
        sf::Sprite normalTextSprite;

        // Sprite for the glitched rectangles for corrupted text
        sf::Sprite glitchTextSprite;

        // Sprite for the Press Any Key message at the bottom
        sf::Sprite pressAnyKeySprite;

        // Sound for the glitch text
        sf::Sound glitchSound;

    public:
        WarningWindow(sf::RenderWindow * window, TextureHolder& textureHolder, SoundHolder& soundHolder);
        void run();
};

#endif // __WARNING_WINDOW_HPP__
