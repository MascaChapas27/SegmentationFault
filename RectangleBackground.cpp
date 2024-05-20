#include "RectangleBackground.hpp"
#include "Utilities.hpp"

RectangleBackground::RectangleBackground(){
    rectangle.setSize(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));
    rectangle.setPosition(0,0);
}

void RectangleBackground::setColor(sf::Color color){
    rectangle.setFillColor(color);
}

sf::Color RectangleBackground::getColor(){
    return rectangle.getFillColor();
}

void RectangleBackground::update(){
    // No need to update a rectangle
}

void RectangleBackground::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    r.draw(rectangle,s);
}
