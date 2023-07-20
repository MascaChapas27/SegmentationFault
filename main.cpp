#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include "ConversationHolder.hpp"
#include "MusicPlayer.hpp"
#include "WarningWindow.hpp"
#include "ControlsManager.hpp"
#include <thread>
#include <chrono>

void conversationTest(TextureHolder& textureHolder, SoundHolder& soundHolder, FontHolder& fontHolder, ConversationHolder& conversationHolder){
    int codigo = 0;

    while(true){
        std::cout << "Enter a conversation code (or -1 to end): ";
        std::cin >> codigo;

        if(codigo == -1) break;

        conversationHolder.start(codigo,textureHolder,soundHolder,fontHolder);

        while(conversationHolder.updateConversation());


    }
    exit(0);
}

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
    fontHolder.load(GabrielaFont,"fonts/gabriela.ttf");
    fontHolder.load(DanielaFont,"fonts/daniela.ttf");

    std::cout << "Loading conversations..." << std::endl;
    // All conversations are initialized
    ConversationHolder conversationHolder(soundHolder);
    conversationHolder.load("files/Conversations.txt");

    // Uncomment to test conversations
    // conversationTest(textureHolder,soundHolder,fontHolder,conversationHolder);

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
    ControlsManager cw(&window,textureHolder,soundHolder);
    cw.showControls(GABRIELA);

    return 0;
}
