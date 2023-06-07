#ifndef __INTERACTION_HPP__
#define __INTERACTION_HPP__

// I don't think it's a good idea to let Utilities.hpp include
// the string library but hey it works on my machine hehaheha
#include "Utilities.hpp"

/*
    An interaction is just a phrase within a Conversation, said
    by a character to another character
*/

class Interaction{

    private:
        // The phrase that is being said
        std::string phrase;

        // The character who speaks (everyone will look at it)
        CharName speaker;

        // The character who listens (the speaker will look at it)
        CharName listener;

        // The emotion the character is feeling (represented by
        // a number which identifies the row inside of the spritesheet)
        int emotion;

    public:
        Interaction();
        std::string getPhrase();
        CharName getSpeaker();
        CharName getListener();
        int getEmotion();
        void setPhrase(std::string phrase);
        void setSpeaker(CharName speaker);
        void setListener(CharName listener);
        void setEmotion(int emotion);
        ~Interaction();
};

#endif // __INTERACTION_HPP__
