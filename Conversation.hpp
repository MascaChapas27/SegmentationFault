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

        // A map of the textboxes (map because there is one for each character)
        std::map<CharName,std::unique_ptr<Textbox>> textboxes;

        // This indicates if the advance key is pressed. If it is, prevent the conversation
        // from advancing. This prevents the user from advancing 999 times by pressing the
        // key once and holding it, forcing the user to release the key and then pressing again
        bool keyPressed;

    public:
        Conversation(std::list<Interaction>& interactions, std::list<CharName>& characters, std::list<CharName>& glitchedCharacters,
                     ResourceHolder<sf::Texture,TextureID>& textureHolder,
                     ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder,
                     ResourceHolder<sf::Font,FontID>& fontHolder);

        bool advance();
        bool update();

        ~Conversation();

};

#endif // __CONVERSATION_HPP__
