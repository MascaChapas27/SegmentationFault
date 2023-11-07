#ifndef __CONVERSATIONHOLDER_HPP__
#define __CONVERSATIONHOLDER_HPP__

#include <map>
#include <memory>
#include "Conversation.hpp"
/*
    This class is like ResourceHolder, but it contains
    all conversarions
*/

class ConversationHolder{

    private:
        // All conversations are in this map
        std::map<int,std::unique_ptr<Conversation>> conversations;

        // This map helps translate names into CharNames
        std::map<std::string,CharName> names;

        // This stores the code of the current conversation
        int currentConversation;

        // This is a sound that plays when the conversation advances
        sf::Sound advanceSound;

        // This indicates if the advance key is pressed. If it is, prevent the conversation
        // from advancing. This prevents the user from advancing 999 times by pressing the
        // key once and holding it, forcing the user to release the key and then pressing again
        bool keyPressed;

    public:
        ConversationHolder();
        void load(std::string path);
        void start(int code);
        bool updateConversation();
        ~ConversationHolder();
};

#endif // __CONVERSATIONHOLDER_HPP__
