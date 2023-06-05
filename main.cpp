#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include <thread>
#include <chrono>
int main(){
    ResourceHolder<sf::Texture,TextureID> textureHolder;
    textureHolder.load(GabrielaTextbox,"sprites\\textbox\\gabrielaTextbox.png");

    ResourceHolder<sf::SoundBuffer,SoundID> soundHolder;
    soundHolder.load(GabrielaSpeaking,"sounds\\speaking\\gabrielaSpeaking.wav");
    soundHolder.load(Glitch0,"sounds\\speaking\\glitch0.wav");

    Textbox t1(GABRIELA,PLAYER,textureHolder.get(GabrielaTextbox),soundHolder.get(GabrielaSpeaking),"fonts\\gabriela.ttf",soundHolder.get(Glitch0));
    t1.setText("amai la kuki xdxdxd\nsi o que eh kuki");
    Textbox t2(GABRIELA,PLAYER,textureHolder.get(GabrielaTextbox),soundHolder.get(GabrielaSpeaking),"fonts\\gabriela.ttf");
    t2.setText("que dices");

    while(t1.update() && t2.update()){

    }

    t1.end();
    t2.end();

    while(t1.update() || t2.update()){

    }
}
