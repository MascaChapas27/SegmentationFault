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

    public:
        Interaction(std::string phrase, CharName speaker, CharName listener);
        std::string getPhrase();
        CharName getSpeaker();
        CharName getListener();
        void setPhrase(std::string phrase);
        void setSpeaker(CharName speaker);
        void setListener(CharName listener);
        ~Interaction();
};

#endif // __INTERACTION_HPP__
