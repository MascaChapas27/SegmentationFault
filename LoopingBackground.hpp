#ifndef __LOOPING_BACKGROUND_HPP__
#define __LOOPING_BACKGROUND_HPP__

#include "AbstractBackground.hpp"
#include "Utilities.hpp"
#include <memory>

class LoopingBackground : public AbstractBackground {
    private:
        // Sprite for the background
        sf::Sprite backgroundSprite;

        // Direction where the loop goes
        Direction whereToLoop;

    public:
        LoopingBackground();
        void setTexture(sf::Texture& tex, Direction whereToLoop);
        void update();
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;
        void add(std::unique_ptr<AbstractBackground> abstBack);

};

#endif // __LOOPING_BACKGROUND_HPP__
