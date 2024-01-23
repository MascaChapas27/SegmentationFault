#include "LoopingBackground.hpp"
#include "Log.hpp"
#include "Utilities.hpp"

LoopingBackground::LoopingBackground(){
    // It's initialized empty but you should set a texture later
}

void LoopingBackground::setTexture(sf::Texture& tex, Direction whereToLoop){
    // The texture for the background is set to repeat itself, then
    // it's assigned to the background sprite
    tex.setRepeated(true);
    this->backgroundSprite.setTexture(tex);

    this->whereToLoop = whereToLoop;

    // The background is expanded so that it's a giant rectangle
    // full of the same tile

    switch(whereToLoop){
    case Direction::DOWN:
    case Direction::UP:
        backgroundSprite.setTextureRect(sf::IntRect(0,0,MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT+tex.getSize().y));
        break;

    case Direction::LEFT:
    case Direction::RIGHT:
        backgroundSprite.setTextureRect(sf::IntRect(0,0,MAIN_WINDOW_WIDTH+tex.getSize().x,MAIN_WINDOW_HEIGHT));
        break;

    default:
        backgroundSprite.setTextureRect(sf::IntRect(0,0,MAIN_WINDOW_WIDTH+tex.getSize().x,MAIN_WINDOW_HEIGHT+tex.getSize().y));
        break;
    }
}

void LoopingBackground::update(){
    switch(whereToLoop){
    case Direction::UP_LEFT:
        // The background moves to the left and up until it loops back and starts over,
        // making it look like it's endless
        backgroundSprite.move(-((float)backgroundSprite.getTexture()->getSize().x/(float)backgroundSprite.getTexture()->getSize().y)/10.f,-1/10.f);
        if(-backgroundSprite.getPosition().x >= backgroundSprite.getTexture()->getSize().x)
        {
            backgroundSprite.setPosition(0,0);
        }
        break;
    }
}

void LoopingBackground::draw(sf::RenderTarget& r, sf::RenderStates s) const {
    r.draw(backgroundSprite,s);
}

void LoopingBackground::add(std::unique_ptr<AbstractBackground> abstBack){

    Log::getInstance()->write("You can't add an abstract background to something that's not a BackgroundContainer!!");
    exit(EXIT_FAILURE);
}
