#ifndef __RECTANGLE_BACKGROUND_HPP__
#define __RECTANGLE_BACKGROUND_HPP__

#include <SFML/Graphics.hpp>
#include "AbstractBackground.hpp"
#include <memory>

/*
    A background formed by just a rectangle and that's it
*/
class RectangleBackground : public AbstractBackground {
    private:
        // Rectangle that forms the background
        sf::RectangleShape rectangle;

    public:
        RectangleBackground();
        void setColor(sf::Color color);
        sf::Color getColor();
        void update();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
};

#endif // __RECTANGLE_BACKGROUND_HPP__

