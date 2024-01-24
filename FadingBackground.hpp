#ifndef __FADING_BACKGROUND_HPP__
#define __FADING_BACKGROUND_HPP__

#include <SFML/Graphics.hpp>
#include "AbstractBackground.hpp"

/*
    A background that starts having a color and slowly changes to
    a different color. Can be used to make the screen fade to black
    or white by drawing the background after everything else (that would
    make it a foreground but anyways)
*/
class FadingBackground : public AbstractBackground {
    private:

        // The initial color the background starts with
        sf::Color initialColor;

        // The final color the background will reach
        sf::Color finalColor;

        // The rectangle that forms the whole background
        sf::RectangleShape backgroundRectangle;

        // How close it will get to the desired color each update
        int fadingSpeed;

        // If this is set to true, then after reaching the final color,
        // it swaps places with the current color, allowing for a loop
        // of color changes
        bool looped;

    public:
        FadingBackground();

        // Sets the current color for the rectangle
        void setCurrentColor(sf::Color color);

        // Sets the initial color for the rectangle
        void setInitialColor(sf::Color color);

        // Sets the final color for the rectangle
        void setFinalColor(sf::Color color);

        // Sets how fast the current color gets close to the final color
        void setFadingSpeed(int fadingSpeed);
        void setLooped(bool looped);
        void update();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
        void add(std::unique_ptr<AbstractBackground> abstBack);
};

#endif // __FADING_BACKGROUND_HPP__
