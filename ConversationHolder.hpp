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

        // This stores the code of the current conversation
        int currentConversation;

        // This is a sound that plays when the conversation advances
        sf::Sound advanceSound;

    public:
        ConversationHolder(ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder);
        void load(std::string path);
        void start(int code, ResourceHolder<sf::Texture,TextureID>& textureHolder,
                   ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder,
                   ResourceHolder<sf::Font,FontID>& fontHolder);
        bool updateConversation();
        ~ConversationHolder();
};

#endif // __CONVERSATIONHOLDER_HPP__
