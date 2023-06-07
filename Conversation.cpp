#include "Conversation.hpp"
#include <assert.h>

Conversation::Conversation(std::list<Interaction>& interactions, std::list<CharName>& characters, std::list<CharName>& glitchedCharacters){
    // The three lists are copied
    this->interactions = interactions;
    this->characters = characters;
    this->glitchedCharacters = glitchedCharacters;
    this->it = interactions.begin();
}

// Once the conversation is loaded, this function creates the textboxes to
// make them appear on the screen
void Conversation::initialize(ResourceHolder<sf::Texture,TextureID>& textureHolder,
                              ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder,
                              ResourceHolder<sf::Font,FontID>& fontHolder){

    // Just in case the conversation occured before, set the iterator to the beginning
    it = interactions.begin();

    // Also, clear the whole map
    textboxes.clear();

    // For every character, a textbox is created
    Position positions[4] = {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
    int numTextboxes = 0;
    for(CharName c : characters){
        switch(c){
        case GABRIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(GABRIELA,PLAYER,textureHolder.get(GabrielaTextbox),soundHolder.get(GabrielaSpeaking),fontHolder.get(Gabriela),positions[numTextboxes%4]));
                auto inserted = textboxes.insert(std::make_pair(GABRIELA,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case DANIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(DANIELA,PLAYER,textureHolder.get(DanielaTextbox),soundHolder.get(DanielaSpeaking),fontHolder.get(Daniela),positions[numTextboxes%4]));
                auto inserted = textboxes.insert(std::make_pair(DANIELA,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case BYSTANDER:
            {
                std::unique_ptr<Textbox> t(new Textbox(BYSTANDER,PLAYER,textureHolder.get(BystanderTextbox),soundHolder.get(Glitch1),fontHolder.get(Gabriela),positions[numTextboxes%4]));
                auto inserted = textboxes.insert(std::make_pair(BYSTANDER,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case PLAYER:
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
        case GABRIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(GABRIELA,PLAYER,textureHolder.get(GabrielaTextbox),soundHolder.get(GabrielaSpeaking),fontHolder.get(Gabriela),positions[numTextboxes%4],soundHolder.get(Glitch0)));
                auto inserted = textboxes.insert(std::make_pair(GABRIELA,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case DANIELA:
            {
                std::unique_ptr<Textbox> t(new Textbox(DANIELA,PLAYER,textureHolder.get(DanielaTextbox),soundHolder.get(DanielaSpeaking),fontHolder.get(Daniela),positions[numTextboxes%4],soundHolder.get(Glitch1)));
                auto inserted = textboxes.insert(std::make_pair(DANIELA,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case BYSTANDER:
            {
                std::unique_ptr<Textbox> t(new Textbox(BYSTANDER,PLAYER,textureHolder.get(BystanderTextbox),soundHolder.get(Glitch1),fontHolder.get(Gabriela),positions[numTextboxes%4],soundHolder.get(Glitch0)));
                auto inserted = textboxes.insert(std::make_pair(BYSTANDER,std::move(t)));
                assert(inserted.second == true);
            }
            break;
        case PLAYER:
            {
                // The player shall not talk
                assert(false);
            }
            break;
        }
        numTextboxes++;
    }

    keyPressed = false;

    advance();
}

bool Conversation::advance(){
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
}

bool Conversation::update(){
    bool shouldAdvance = false;
    for(auto i = textboxes.begin(); i != textboxes.end(); i++){
        CharName lookingAt = i->second->getLookingAt();
        int x = lookingAt == PLAYER ? -1 : textboxes[lookingAt]->getX();
        int y = lookingAt == PLAYER ? -1 : textboxes[lookingAt]->getY();
        if(i->second->update(keyPressed,x,y)) shouldAdvance = true;
    }
    return shouldAdvance;
}

Conversation::~Conversation(){

}
