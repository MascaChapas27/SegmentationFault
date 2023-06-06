#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include "Conversation.hpp"
#include <thread>
#include <chrono>
int main(){
    // All textures are initialized
    ResourceHolder<sf::Texture,TextureID> textureHolder;
    textureHolder.load(GabrielaTextbox,"sprites\\textbox\\gabrielaTextbox.png");

    // All sound buffers are initialized
    ResourceHolder<sf::SoundBuffer,SoundID> soundHolder;
    soundHolder.load(GabrielaSpeaking,"sounds\\speaking\\gabrielaSpeaking.wav");
    soundHolder.load(Glitch0,"sounds\\speaking\\glitch0.wav");
    soundHolder.load(AdvanceConversation,"sounds\\speaking\\advanceConversation.wav");

    // All fonts are initialized
    ResourceHolder<sf::Font,FontID> fontHolder;
    fontHolder.load(Gabriela,"fonts\\gabriela.ttf");

    std::list<Interaction> interactions;
    Interaction i("",GABRIELA,PLAYER);
    i.setPhrase("hey how is it\ngoing if i can\nask");
    interactions.push_back(i);
    i.setPhrase("who am i even\ntalking to lmao");
    interactions.push_back(i);
    i.setPhrase("i dont care i\nwill just keep talking");
    interactions.push_back(i);

    std::list<CharName> chars;
    std::list<CharName> glitchChars = {GABRIELA};

    Conversation c(interactions,chars,glitchChars,textureHolder,soundHolder,fontHolder);

    bool keepGoing = true;

    while(keepGoing){
        if(c.update()) keepGoing = c.advance();
    }

}
