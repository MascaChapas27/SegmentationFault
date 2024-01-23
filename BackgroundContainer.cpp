#include "BackgroundContainer.hpp"

BackgroundContainer::BackgroundContainer(){

}

void BackgroundContainer::update(){
    for(std::unique_ptr<AbstractBackground>& abstBack : backgrounds){
        abstBack->update();
    }
}

void BackgroundContainer::draw(sf::RenderTarget& r, sf::RenderStates s) const {

    // I have to use pointers the old way because if I do it with a foreach
    // like in BackgroundContainer::update() it complains because of the &
    auto it = backgrounds.begin();

    while(it != backgrounds.end()){
        (*it).get()->draw(r,s);
        it++;
    }
}

void BackgroundContainer::add(std::unique_ptr<AbstractBackground> abstBack){
    // It inserts at the end, so the first elements you insert will be drawn first, and
    // the others will be drawn on top of it
    backgrounds.insert(backgrounds.end(),std::move(abstBack));
}
