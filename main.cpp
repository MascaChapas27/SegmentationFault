#include "Textbox.hpp"
#include <thread>
#include <chrono>
int main(){
    Textbox t1(GABRIELA,PLAYER,"sprites\\textbox\\gabrielaTextbox.png","sounds\\speaking\\gabrielaSpeaking.wav","fonts\\gabriela.ttf","sounds\\speaking\\glitch0.wav");
    t1.setText("amai la kuki xdxdxd\nsi o que eh kuki");
    Textbox t2(GABRIELA,PLAYER,"sprites\\textbox\\gabrielaTextbox.png","sounds\\speaking\\gabrielaSpeaking.wav","fonts\\gabriela.ttf");
    t2.setText("que dices");

    while(t1.update() && t2.update()){

    }

    t1.end();
    t2.end();

    while(t1.update() || t2.update()){

    }
}
