#include "Conversation.hpp"
#include <assert.h>

Conversation::Conversation(std::list<Interaction>& interactions, std::list<CharName>& characters, std::list<CharName>& glitchedCharacters,
                           ResourceHolder<sf::Texture,TextureID>& textureHolder,
                           ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder,
                           ResourceHolder<sf::Font,FontID>& fontHolder){
    // The list of interactions is copied
    this->interactions = interactions;

    // For every character, a textbox is created
    Position positions[4] = {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
    int numTextboxes = 0;
    for(CharName c : characters){
        switch(c){
        case GABRIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(GABRIELA,NULL,textureHolder.get(GabrielaTextbox),soundHolder.get(GabrielaSpeaking),fontHolder.get(Gabriela),positions[numTextboxes%4]));
                auto inserted = textboxes.insert(std::make_pair(GABRIELA,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        default:
            break;
        }
        numTextboxes++;
    }

    for(CharName c : glitchedCharacters){
        switch(c){
        case GABRIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(GABRIELA,NULL,textureHolder.get(GabrielaTextbox),soundHolder.get(GabrielaSpeaking),fontHolder.get(Gabriela),positions[numTextboxes%4],soundHolder.get(Glitch0)));
                auto inserted = textboxes.insert(std::make_pair(GABRIELA,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        default:
            break;
        }
        numTextboxes++;
    }

    keyPressed = false;

    advance();
}

bool Conversation::advance(){
    // if there are no more interactions, then end everything
    if(interactions.empty()){
        for(auto t = textboxes.begin(); t != textboxes.end(); t++){
            // All textbox windows are told to end
            t->second->end();
        }
        return false;
    }

    // Get the first interaction and delete it
    Interaction i = interactions.front();
    interactions.pop_front();

    // The speaker speaks the phrase of the interaction
    textboxes[i.getSpeaker()]->setText(i.getPhrase());

    // For every participant in the conversation...
    for(auto t = textboxes.begin(); t != textboxes.end(); t++){
        if(t->second->getSpeaker() == i.getSpeaker())
            // The speaker will look at the listener
            // If the listener is the PLAYER, then there will be no listener
            t->second->setLookingAt(i.getListener() == PLAYER ? NULL : std::move(textboxes[i.getListener()]));
        else
            // Every other participant (including the listener) will look
            // at the speaker
            t->second->setLookingAt(std::move(textboxes[i.getSpeaker()]));
    }
    return true;
}

bool Conversation::update(){
    bool shouldAdvance = false;
    for(auto i = textboxes.begin(); i != textboxes.end(); i++)
        if(i->second->update(keyPressed)) shouldAdvance = true;
    return shouldAdvance;
}

Conversation::~Conversation(){

}
