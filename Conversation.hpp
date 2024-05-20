#ifndef __CONVERSATION_HPP__
#define __CONVERSATION_HPP__

#include <list>
#include "Interaction.hpp"
#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include "FadingBackground.hpp"

/*
    A conversation is a moment of the gameplay in which
    textboxes appear on the screen and characters say stuff.
*/

class Conversation{

    private:
        // A list of all the interactions that form the conversation
        std::list<Interaction> interactions;

        // A list of all normal characters that participate
        std::list<CharName> characters;

        // A list of all glitched characters that participate
        std::list<CharName> glitchedCharacters;

        // A capture of the screen to show it in the background
        sf::Texture captureTexture;
        sf::Sprite captureSprite;

        // Black rectangles for the top and bottom part of the screen
        sf::RectangleShape upRectangle;
        sf::RectangleShape downRectangle;

        // Background with cool squares
        FadingBackground background;

        // Chatboxes that contain the text spoken by every character
        //std::list<Chatbox> chatboxes;

        // An iterator that points at the current Interaction
        std::list<Interaction>::iterator it;

        // 0 = starting; 1 = started; 2 = ending; 3 = ended
        int state;

    public:
        Conversation(std::list<Interaction>& interactions, std::list<CharName>& characters, std::list<CharName>& glitchedCharacters);

        bool advance();
        void initialize();
        bool update(bool checkIfAdvance);

        ~Conversation();

};

#endif // __CONVERSATION_HPP__
