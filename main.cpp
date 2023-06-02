#include "Textbox.hpp"
#include <thread>
#include <chrono>
int main(){
    std::string gabrielaSpeakingSounds[3];
    gabrielaSpeakingSounds[0] = "sounds\\speaking\\gabriela\\gabrielaSpeaking0.wav";
    gabrielaSpeakingSounds[1] = "sounds\\speaking\\gabriela\\gabrielaSpeaking1.wav";
    gabrielaSpeakingSounds[2] = "sounds\\speaking\\gabriela\\gabrielaSpeaking2.wav";
    Textbox t(GABRIELA,PLAYER,"sprites\\textbox\\gabrielaTextbox.png",gabrielaSpeakingSounds,"fonts\\gabriela.ttf");
    t.setText("amai la kuki xdxdxd\nsi o que eh kuki");
    while(t.update()){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
