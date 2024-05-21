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

    state = ConversationState::STARTING;
}

// The player pressed the advance key
void Conversation::advance(){

    switch(state){
        case ConversationState::WAITING:

            background.setInitialColor(background.getColor());
            background.setFinalColor(sf::Color(255,255,255,0));
            state = ConversationState::ENDING;

            // Left character is who it should be? What about right character?
            // Change to HIDING_???_CHAR depending on that

            // If not, advance interaction iterator
            // The end is reached? state is not ENDING

            // If everything is OK

            break;
        case ConversationState::SPEAKING:
            // Skip the speaking and show the final text immediately

            // The final text had a sudden end character?? Then keep speaking
            // The final text didn't?? Then waiting
            // PRO TIP: in both cases set the state to WAITING but call advance() once
            // again in the first case only
            break;
    }
}

// Update the conversation
// If it returns true: keep going
// If it returns false: it's joever
bool Conversation::update(){
    background.update();

    switch(state){
        case ConversationState::STARTING:
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
                state = ConversationState::WAITING;
            }

            break;
        case ConversationState::WAITING:

            break;
        case ConversationState::ENDING:
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
                state = ConversationState::ENDED;
            }

            break;

        case ConversationState::ENDED:
            return false;
            break;
    }

    window.clear();

    window.draw(captureSprite);
    window.draw(background);
    window.draw(upRectangle);
    window.draw(downRectangle);

    window.display();

    return true;
}

Conversation::~Conversation(){

}
