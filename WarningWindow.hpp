#ifndef __WARNING_WINDOW_HPP__
#define __WARNING_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "MusicPlayer.hpp"
#include "FadingBackground.hpp"

// Class for the warning window that appears at the beginning
class WarningWindow
{
    protected:
        WarningWindow();

        static WarningWindow * warningWindow;

    private:

        // Background that says "warning" a lot of times plus a black fade
        FadingBackground background;

        // Foreground that makes everything black when you press any key
        FadingBackground foreground;

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

        // Warn the players about what could happen if
        //
        //
        //
        bool run();

        // NEVER CLONE A SINGLETON
        WarningWindow(WarningWindow &other) = delete;

        // NEVER ASSIGN A SINGLETON
        void operator=(const WarningWindow &) = delete;

        // Get the instance
        static WarningWindow * getInstance();
};

#endif // __WARNING_WINDOW_HPP__
