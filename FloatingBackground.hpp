#ifndef __FLOATING_BACKGROUND_HPP__
#define __FLOATING_BACKGROUND_HPP__

#include <vector>
#include <SFML/Graphics.hpp>
#include "AbstractBackground.hpp"
#include <memory>

/*
    A background formed by many sprites that are the same
    floating randomly
*/
class FloatingBackground : public AbstractBackground {
    private:
        // Vector of floating sprites that show in the background
        std::vector<sf::Sprite> floatingSprites;

        // Vector of speeds for every floating sprite
        std::vector<sf::Vector2f> floatingSpeeds;
    public:
        FloatingBackground();

        // Sets the texture and number of floating sprites
        void setTextureAndNumber(sf::Texture& texture, int numSprites);
        void setColor(sf::Color color);
        sf::Color getColor();
        void update();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
        void add(std::unique_ptr<AbstractBackground> abstBack);
};

#endif // __FLOATING_BACKGROUND_HPP__
