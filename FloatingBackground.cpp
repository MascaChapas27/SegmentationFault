#include "FloatingBackground.hpp"
#include "Utilities.hpp"
#include "Log.hpp"

FloatingBackground::FloatingBackground(){

}

void FloatingBackground::setTextureAndNumber(sf::Texture& texture, int numSprites){

    // Clear the current data
    floatingSpeeds.clear();
    floatingSprites.clear();

    // The vector of floating symbols is initialized
    for(int i=0;i<numSprites;i++){
        sf::Sprite s;
        int randomScale = util::RandomBetween(1,4);
        s.setPosition(rand()%MAIN_WINDOW_WIDTH-s.getTextureRect().width*s.getScale().x/2,
                      rand()%MAIN_WINDOW_HEIGHT-s.getTextureRect().height*s.getScale().y/2);
        s.setScale(randomScale,randomScale);
        s.setColor(FLOATING_CONTROLS_COLOR);
        s.setTexture(texture);
        floatingSprites.push_back(s);

        // The speeds too
        floatingSpeeds.push_back(sf::Vector2f(1.0-(rand()%201)/100.0,1.0-(rand()%201)/100.0));
    }
}

void FloatingBackground::update(){
    for(std::vector<sf::Sprite>::size_type i=0;i<floatingSprites.size();i++){
        floatingSprites[i].move(floatingSpeeds[i]);
        if(floatingSprites[i].getPosition().x > MAIN_WINDOW_WIDTH)
            floatingSprites[i].setPosition(-(floatingSprites[i].getTextureRect().width*floatingSprites[i].getScale().x),
                                            floatingSprites[i].getPosition().y);

        else if(floatingSprites[i].getPosition().x < -(floatingSprites[i].getTextureRect().width*floatingSprites[i].getScale().x))
            floatingSprites[i].setPosition(MAIN_WINDOW_WIDTH,
                                            floatingSprites[i].getPosition().y);

        if(floatingSprites[i].getPosition().y > MAIN_WINDOW_HEIGHT)
            floatingSprites[i].setPosition(floatingSprites[i].getPosition().x,
                                            -(floatingSprites[i].getTextureRect().height*floatingSprites[i].getScale().y));

        else if(floatingSprites[i].getPosition().y < -(floatingSprites[i].getTextureRect().height*floatingSprites[i].getScale().y))
            floatingSprites[i].setPosition(floatingSprites[i].getPosition().x,
                                            MAIN_WINDOW_HEIGHT);
    }
}

void FloatingBackground::setColor(sf::Color color){
    // Nah
}

sf::Color FloatingBackground::getColor(){
    // I don't care
    return sf::Color::Transparent;
}

void FloatingBackground::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    for(std::vector<sf::Sprite>::size_type i=0;i<floatingSprites.size();i++){
        r.draw(floatingSprites[i],s);
    }
}

void FloatingBackground::add(std::unique_ptr<AbstractBackground> abstBack){
    Log::getInstance()->write("You can't add an abstract background to something that's not a BackgroundContainer!!");
    exit(EXIT_FAILURE);
}
