#ifndef __CONVERSATION_HPP__
#define __CONVERSATION_HPP__

#include <list>
#include "Interaction.hpp"
#include "Textbox.hpp"
#include "ResourceHolder.hpp"

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

        // A map of the textboxes (map because there is one for each character)
        std::map<CharName,std::unique_ptr<Textbox>> textboxes;

        // An iterator that points at the current Interaction
        std::list<Interaction>::iterator it;

    public:
        Conversation(std::list<Interaction>& interactions, std::list<CharName>& characters, std::list<CharName>& glitchedCharacters);

        bool advance();
        void initialize(ResourceHolder<sf::Texture,TextureID>& textureHolder,
                                      ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder,
                                      ResourceHolder<sf::Font,FontID>& fontHolder);
        bool update(bool checkIfAdvance);

        ~Conversation();

};

#endif // __CONVERSATION_HPP__
