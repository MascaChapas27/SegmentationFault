#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include "ConversationHolder.hpp"
#include "MusicPlayer.hpp"
#include "WarningWindow.hpp"
#include "ControlsWindow.hpp"
#include <thread>
#include <chrono>

int main(){
    std::cout << "Loading textures..." << std::endl;
    // All textures are initialized
    TextureHolder textureHolder;
    textureHolder.load(GabrielaTextbox,"sprites/textbox/gabrielaTextbox.png");
    textureHolder.load(DanielaTextbox,"sprites/textbox/danielaTextbox.png");
    textureHolder.load(BystanderTextbox,"sprites/textbox/bystanderTextbox.png");
    textureHolder.load(WarningBackground,"sprites/warning/warningBackground.png");
    textureHolder.load(WarningNormalText,"sprites/warning/warningNormalText.png");
    textureHolder.load(WarningGlitchText,"sprites/warning/warningGlitchText.png");
    textureHolder.load(WarningPressEnter,"sprites/warning/warningPressEnter.png");
    textureHolder.load(ControlsGabriela,"sprites/controls/controlsGabriela.png");

    std::cout << "Loading sound effects..." << std::endl;
    // All sound buffers are initialized
    SoundHolder soundHolder;
    soundHolder.load(GabrielaSpeaking,"sounds/speaking/gabrielaSpeaking.wav");
    soundHolder.load(DanielaSpeaking,"sounds/speaking/danielaSpeaking.wav");
    soundHolder.load(Glitch0,"sounds/glitch/glitch0.wav");
    soundHolder.load(Glitch1,"sounds/glitch/glitch1.wav");
    soundHolder.load(AdvanceConversation,"sounds/speaking/advanceConversation.wav");
    soundHolder.load(ControlsGlitchSound,"sounds/glitch/controlsGlitchSound.wav");

    std::cout << "Loading music..." << std::endl;
    // Al music themes are initialized
    MusicPlayer musicPlayer;
    musicPlayer.load(WarningMusic,"music/warning/warningMusic.wav");

    std::cout << "Loading fonts..." << std::endl;
    // All fonts are initialized
    FontHolder fontHolder;
    fontHolder.load(Gabriela,"fonts/gabriela.ttf");
    fontHolder.load(Daniela,"fonts/daniela.ttf");

    std::cout << "Loading conversations..." << std::endl;
    // All conversations are initialized
    ConversationHolder conversationHolder(soundHolder);
    conversationHolder.load("files/Conversations.txt");

    // This is the main window we are going to use through the
    // whole game
    sf::RenderWindow window(sf::VideoMode(800,600),"amai");
    window.setFramerateLimit(60);

    // The warning window is created using a pointer to the main window
    WarningWindow ww(&window,textureHolder,soundHolder);

    // Then, the warning window runs (and the warning music plays)
    musicPlayer.play(WarningMusic);
    ww.run();

    // When the warning window ends, then the music stops as well
    musicPlayer.stop();

    // The controls window is created with a pointer to the main window
    // as well (this main window will always be used)
    ControlsWindow cw(&window,textureHolder,soundHolder);
    cw.run();

    return 0;
}
