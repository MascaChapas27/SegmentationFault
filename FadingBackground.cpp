#include "FadingBackground.hpp"
#include "Utilities.hpp"
#include "Log.hpp"

FadingBackground::FadingBackground(){
    fadingSpeed = 1;
}

void FadingBackground::setColor(sf::Color color){
    background->setColor(color);
}

sf::Color FadingBackground::getColor(){
    return background->getColor();
}

void FadingBackground::setInitialColor(sf::Color color){
    this->initialColor = color;
}

void FadingBackground::setFinalColor(sf::Color color){
    this->finalColor = color;
}

void FadingBackground::setFadingSpeed(int fadingSpeed){
    this->fadingSpeed = fadingSpeed;
}

// Helper function: given the old value, the goal and the fading speed
// returns the new value
int findNewColor(int old, int goal, int fadingSpeed){
    // If the value is close enough, return the goal directly
    if(abs(old-goal) <= fadingSpeed) return goal;

    // If the value is far and too big, make it smaller
    else if(old > goal) return old - fadingSpeed;

    // Otherwise, the value is too small. Make it bigger
    else return old + fadingSpeed;
}

void FadingBackground::setLooped(bool looped)
{
    this->looped = looped;
}

void FadingBackground::update(){
    background->update();

    sf::Color newColor = getColor();

    // For each channel make it slightly closer
    newColor.r = findNewColor(newColor.r,finalColor.r,fadingSpeed);
    newColor.g = findNewColor(newColor.g,finalColor.g,fadingSpeed);
    newColor.b = findNewColor(newColor.b,finalColor.b,fadingSpeed);
    newColor.a = findNewColor(newColor.a,finalColor.a,fadingSpeed);

    setColor(newColor);

    // This one is classic
    if(looped && newColor == finalColor){
        sf::Color aux = finalColor;
        finalColor = initialColor;
        initialColor = aux;
    }
}

void FadingBackground::setBackground(std::unique_ptr<AbstractBackground> background){
    this->background = std::move(background);
}

void FadingBackground::draw(sf::RenderTarget& r, sf::RenderStates s) const{
    r.draw(*background,s);
}

void FadingBackground::add(std::unique_ptr<AbstractBackground> abstBack){
    Log::getInstance()->write("You can't add an abstract background to something that's not a BackgroundContainer!!");
    exit(EXIT_FAILURE);
}
