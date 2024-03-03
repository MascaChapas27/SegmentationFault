#ifndef __BACKGROUND_CONTAINER_HPP__
#define __BACKGROUND_CONTAINER_HPP__

#include <SFML/Graphics.hpp>
#include "AbstractBackground.hpp"
#include <list>
#include <memory>

/*
    COMPOSITE PATTERN
    Acts like a background, but allows for backgrounds formed by
    many backgrounds at the same time
*/
class BackgroundContainer : public AbstractBackground {
    private:
        // List of backgrounds contained in this container
        std::list<std::unique_ptr<AbstractBackground>> backgrounds;

    public:

        // Updates all backgrounds contained
        void update();

        // Draws all backgrounds contained
        void draw(sf::RenderTarget& r, sf::RenderStates s) const;

        // Adds the given pointer to the list of backgrounds
        void add(std::unique_ptr<AbstractBackground> abstBack);

        BackgroundContainer();

};

#endif // __BACKGROUND_CONTAINER_HPP__
