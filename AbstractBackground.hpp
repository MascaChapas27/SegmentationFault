#ifndef __ABSTRACT_BACKGROUND_HPP__
#define __ABSTRACT_BACKGROUND_HPP__

#include <SFML/Graphics.hpp>
#include <memory>

/*
    A background that can be any type of background,
    great for cool effects in the background as its name suggests
*/
class AbstractBackground : public sf::Drawable {
    public:
        // Virtual methods, must be implemented in children classes
        virtual void setColor(sf::Color color)=0;
        virtual sf::Color getColor()=0;
        virtual void update()=0;
        virtual void draw(sf::RenderTarget& r, sf::RenderStates s) const=0;
};

#endif // __ABSTRACT_BACKGROUND_HPP__
