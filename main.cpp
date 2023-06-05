#include "Textbox.hpp"
#include <thread>
#include <chrono>
int main(){
    std::string gabrielaSpeakingSounds[3];
    gabrielaSpeakingSounds[0] = "sounds\\speaking\\gabriela\\gabrielaSpeaking0.wav";
    gabrielaSpeakingSounds[1] = "sounds\\speaking\\gabriela\\gabrielaSpeaking1.wav";
    gabrielaSpeakingSounds[2] = "sounds\\speaking\\gabriela\\gabrielaSpeaking2.wav";
    Textbox t1(GABRIELA,PLAYER,"sprites\\textbox\\gabrielaTextbox.png",gabrielaSpeakingSounds,"fonts\\gabriela.ttf", true);
    t1.setText("amai la kuki xdxdxd\nsi o que eh kuki");
    Textbox t2(GABRIELA,PLAYER,"sprites\\textbox\\gabrielaTextbox.png",gabrielaSpeakingSounds,"fonts\\gabriela.ttf", false);
    t2.setText("que dices");
    while(t1.update() && t2.update()){

    }

    t1.end();
    t2.end();

    while(t1.update() || t2.update()){

    }
}
