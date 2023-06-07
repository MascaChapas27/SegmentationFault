#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include "ConversationHolder.hpp"
#include <thread>
#include <chrono>
int main(){
    // All textures are initialized
    ResourceHolder<sf::Texture,TextureID> textureHolder;
    textureHolder.load(GabrielaTextbox,"sprites\\textbox\\gabrielaTextbox.png");
    textureHolder.load(DanielaTextbox,"sprites\\textbox\\danielaTextbox.png");
    textureHolder.load(BystanderTextbox,"sprites\\textbox\\bystanderTextbox.png");

    // All sound buffers are initialized
    ResourceHolder<sf::SoundBuffer,SoundID> soundHolder;
    soundHolder.load(GabrielaSpeaking,"sounds\\speaking\\gabrielaSpeaking.wav");
    soundHolder.load(DanielaSpeaking,"sounds\\speaking\\danielaSpeaking.wav");
    soundHolder.load(Glitch0,"sounds\\speaking\\glitch0.wav");
    soundHolder.load(Glitch1,"sounds\\speaking\\glitch1.wav");
    soundHolder.load(AdvanceConversation,"sounds\\speaking\\advanceConversation.wav");

    // All fonts are initialized
    ResourceHolder<sf::Font,FontID> fontHolder;
    fontHolder.load(Gabriela,"fonts\\gabriela.ttf");
    fontHolder.load(Daniela,"fonts\\daniela.ttf");

    // All conversations are initialized
    ConversationHolder conversationHolder(soundHolder);
    conversationHolder.load("files\\Conversations.txt");

    int codigo = 0;

    while(true){
        std::cout << "Enter a conversation code (or -1 to end): ";
        std::cin >> codigo;

        if(codigo == -1) break;

        conversationHolder.start(codigo,textureHolder,soundHolder,fontHolder);

        while(conversationHolder.updateConversation()){
        }

    }
}
