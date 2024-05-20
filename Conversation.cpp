#include "Conversation.hpp"
#include "LoopingBackground.hpp"
#include "ResourceHolder.hpp"
#include "Utilities.hpp"
#include <assert.h>

Conversation::Conversation(std::list<Interaction>& interactions, std::list<CharName>& characters, std::list<CharName>& glitchedCharacters){
    // The three lists are copied
    this->interactions = interactions;
    this->characters = characters;
    this->glitchedCharacters = glitchedCharacters;

    // The iterator points at the beginning
    it = interactions.begin();

    // The rectangles are created
    upRectangle.setSize(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT/7));
    upRectangle.setFillColor(sf::Color::Black);
    upRectangle.setOrigin(upRectangle.getSize().x/2,0);

    downRectangle.setSize(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT/7));
    downRectangle.setFillColor(sf::Color::Black);
    downRectangle.setOrigin(downRectangle.getSize().x/2,downRectangle.getSize().y);

    // The looping background is created
    std::unique_ptr<LoopingBackground> loopingBackground(new LoopingBackground());
    loopingBackground->setTexture(TextureHolder::getTextureInstance()->get(TextureID::SquareBackground),Direction::UP_LEFT);

    // Now put the looping background in the fading background
    background.setBackground(std::move(loopingBackground));
}

// Once the conversation is loaded, this function starts it
void Conversation::initialize(){
    /*
    TextureHolder * textureHolder = TextureHolder::getTextureInstance();
    SoundHolder * soundHolder = SoundHolder::getSoundInstance();
    FontHolder * fontHolder = FontHolder::getFontInstance();

    // Just in case the conversation occured before, set the iterator to the beginning
    it = interactions.begin();

    // Also, clear the whole map
    textboxes.clear();

    // For every character, a textbox is created
    int numTextboxes = 0;
    for(CharName c : characters){
        switch(c){
        case CharName::GABRIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(c,CharName::PLAYER,textureHolder->get(TextureID::GabrielaTextbox),soundHolder->get(SoundID::GabrielaSpeaking),fontHolder->get(FontID::GabrielaFont),static_cast<TextboxPosition>(numTextboxes)));
                auto inserted = textboxes.insert(std::make_pair(c,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case CharName::DANIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(c,CharName::PLAYER,textureHolder->get(TextureID::DanielaTextbox),soundHolder->get(SoundID::DanielaSpeaking),fontHolder->get(FontID::DanielaFont),static_cast<TextboxPosition>(numTextboxes)));
                auto inserted = textboxes.insert(std::make_pair(c,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case CharName::BYSTANDER:
            {
                std::unique_ptr<Textbox> t(new Textbox(c,CharName::PLAYER,textureHolder->get(TextureID::BystanderTextbox),soundHolder->get(SoundID::Glitch1),fontHolder->get(FontID::GabrielaFont),static_cast<TextboxPosition>(numTextboxes)));
                auto inserted = textboxes.insert(std::make_pair(c,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case CharName::PLAYER:
            {
                // The player shall not talk
                assert(false);
            }
            break;
        }
        numTextboxes++;
    }
    // For the glitched characters it's the same thing but with a glitched textbox
    for(CharName c : glitchedCharacters){
        switch(c){
        case CharName::GABRIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(c,CharName::PLAYER,textureHolder->get(TextureID::GabrielaTextbox),soundHolder->get(SoundID::GabrielaSpeaking),fontHolder->get(FontID::GabrielaFont),static_cast<TextboxPosition>(numTextboxes),soundHolder->get(SoundID::Glitch0)));
                auto inserted = textboxes.insert(std::make_pair(c,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case CharName::DANIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(c,CharName::PLAYER,textureHolder->get(TextureID::DanielaTextbox),soundHolder->get(SoundID::DanielaSpeaking),fontHolder->get(FontID::DanielaFont),static_cast<TextboxPosition>(numTextboxes),soundHolder->get(SoundID::Glitch1)));
                auto inserted = textboxes.insert(std::make_pair(c,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case CharName::BYSTANDER:
            {
                std::unique_ptr<Textbox> t(new Textbox(c,CharName::PLAYER,textureHolder->get(TextureID::BystanderTextbox),soundHolder->get(SoundID::Glitch1),fontHolder->get(FontID::GabrielaFont),static_cast<TextboxPosition>(numTextboxes),soundHolder->get(SoundID::Glitch0)));
                auto inserted = textboxes.insert(std::make_pair(c,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case CharName::PLAYER:
            {
                // The player shall not talk
                assert(false);
            }
            break;
        }
        numTextboxes++;
    }
    */

    background.setColor(sf::Color(255,255,255,0));
    background.setInitialColor(sf::Color(255,255,255,0));
    background.setFinalColor(sf::Color(255,255,255,100));

    upRectangle.setPosition(MAIN_WINDOW_WIDTH/2.0,-upRectangle.getSize().y);
    downRectangle.setPosition(MAIN_WINDOW_WIDTH/2.0,MAIN_WINDOW_HEIGHT + downRectangle.getSize().y);

    sf::Vector2u windowSize = window.getSize();
    captureTexture.create(windowSize.x, windowSize.y);
    captureTexture.update(window);
    captureSprite.setTexture(captureTexture);
    captureSprite.setPosition(0,0);

    state = 0;
}

// Advances the current conversation.
// True: The conversation can still go
// False: The conversation is over
bool Conversation::advance(){
    return state < 3;
    /*
    // if there are no more interactions, then end everything
    if(it == interactions.end()){
        bool keepGoing = false;
        for(auto t = textboxes.begin(); t != textboxes.end(); t++){
            // All textbox windows are told to end
            t->second->end();
            // If at least one texbox is not closed, the conversation can't end
            if(!t->second->isClosed()) keepGoing = true;
        }
        return keepGoing;
    }

    // Get the next interaction and advance the pointer

    Interaction i = *it;
    it++;

    // The speaker speaks the phrase of the interaction
    textboxes[i.getSpeaker()]->setText(i.getPhrase());
    textboxes[i.getSpeaker()]->setEmotion(i.getEmotion());

    // For every participant in the conversation...
    for(auto t = textboxes.begin(); t != textboxes.end(); t++){
        if(t->second->getSpeaker() == i.getSpeaker()){
            // The speaker will look at the listener
            t->second->setLookingAt(i.getListener());
        } else {
            // Every other participant (including the listener) will look
            // at the speaker
            t->second->setLookingAt(i.getSpeaker());
        }

    }
    return true;
    */
}

// Update the conversation, which returns true if the conversation
// should advance, or false if the conversation is OK right now and
// doesn't need to advance
// bool checkIfAdvance means we pressed the advance key but maybe
// the character didn't finish speaking
bool Conversation::update(bool checkIfAdvance){
    background.update();

    bool shouldAdvance = false;

    switch(state){
        case 0:
            // Move the rectangle at the top
            if(upRectangle.getPosition().y < 0){
                sf::Vector2f pos = upRectangle.getPosition();
                pos.y++;
                upRectangle.setPosition(pos);
            }

            // Move the rectangle at the bottom
            if(downRectangle.getPosition().y > MAIN_WINDOW_HEIGHT){
                sf::Vector2f pos = downRectangle.getPosition();
                pos.y--;
                downRectangle.setPosition(pos);
            }

            if(upRectangle.getPosition().y == 0 && downRectangle.getPosition().y == MAIN_WINDOW_HEIGHT){
                shouldAdvance = true;
                state = 1;
            }

            break;
        case 1:
            if(checkIfAdvance){
                background.setInitialColor(background.getColor());
                background.setFinalColor(sf::Color(255,255,255,0));
                state = 2;
                shouldAdvance = true;
            }

            break;
        case 2:
            // Move the rectangle at the top
            if(upRectangle.getPosition().y > -upRectangle.getSize().y){
                sf::Vector2f pos = upRectangle.getPosition();
                pos.y--;
                upRectangle.setPosition(pos);
            }

            // Move the rectangle at the bottom
            if(downRectangle.getPosition().y < MAIN_WINDOW_HEIGHT+downRectangle.getSize().y){
                sf::Vector2f pos = downRectangle.getPosition();
                pos.y++;
                downRectangle.setPosition(pos);
            }

            if(upRectangle.getPosition().y == -upRectangle.getSize().y && downRectangle.getPosition().y == MAIN_WINDOW_HEIGHT+downRectangle.getSize().y){
                shouldAdvance = true;
                state = 3;
            }
        case 3:
            shouldAdvance = true;
            break;
    }

    window.clear();

    window.draw(captureSprite);
    window.draw(background);
    window.draw(upRectangle);
    window.draw(downRectangle);

    window.display();

    return shouldAdvance;

    /*
    // Helper boolean, stores if we should advance in the conversation
    bool shouldAdvance = false;
    for(auto i = textboxes.begin(); i != textboxes.end(); i++){
        // For every textbox, set the x and y coordinates it looks at
        // depending on its lookingAt value (maybe there is a better
        // way to do this)
        CharName lookingAt = i->second->getLookingAt();
        // If the character looks at the player, set both coordinates
        // to -1
        int x = lookingAt == CharName::PLAYER ? -1 : textboxes[lookingAt]->getX();
        int y = lookingAt == CharName::PLAYER ? -1 : textboxes[lookingAt]->getY();
        // Update the current textbox. If the update function returns true,
        // then it means we should advance in the conversation
        if(i->second->update(checkIfAdvance,x,y)) shouldAdvance = true;
    }
    return shouldAdvance;
    */
}

Conversation::~Conversation(){

}
