#ifndef __ABSTRACT_BACKGROUND_HPP__
#define __ABSTRACT_BACKGROUND_HPP__

#include <SFML/Graphics.hpp>

/*
    A background that can be any type of background,
    great for cool effects in the background as its name suggests
*/
class AbstractBackground : public sf::Drawable {
    public:
        // Virtual methods, must be implemented in children classes
        virtual void update()=0;
        virtual void draw(sf::RenderTarget& r, sf::RenderStates s) const=0;
        virtual void add(std::unique_ptr<AbstractBackground> abstBack)=0;
};

#endif // __ABSTRACT_BACKGROUND_HPP__
