#include "Textbox.hpp"
#include "ResourceHolder.hpp"
#include "ConversationHolder.hpp"
#include "MusicPlayer.hpp"
#include "WarningWindow.hpp"
#include "ControlsManager.hpp"
#include "Utilities.hpp"
#include <thread>
#include <chrono>
#include <ctime>

// Only definition of the global variables
std::ofstream logFile;
MusicPlayer musicPlayer;

void conversationTest(TextureHolder& textureHolder, SoundHolder& soundHolder, FontHolder& fontHolder, ConversationHolder& conversationHolder){
    int code = 0;
    std::cout << "Welcome to conversation debug mode!" << std::endl;

    while(true){
        std::cout << "Enter a conversation code (or -1 to end): ";
        std::cin >> code;

        if(code == -1) break;

        conversationHolder.start(code,textureHolder,soundHolder,fontHolder);

        while(conversationHolder.updateConversation());
    }



    exit(EXIT_SUCCESS);
}

int main(){

    // This thing makes error messages disappear because they keep appearing oh god
    // they are everywhere go straight to hell and dont come back
    sf::err().rdbuf(NULL);

    // The error messages will go to this amazingly global error file
    logFile.open(LOG_FILE_PATH,std::ios_base::app);
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);

    logFile << "----------------------------------------------" << std::endl;
    logFile << "Log File created. Today's date is: " << asctime(ti) << std::endl << std::endl;

    // Some graphics cards are not good enough for some texture sizes, so let's check it
    checkGraphicsCard();

    // This is the main window we are going to use through the
    // whole game
    sf::RenderWindow window(sf::VideoMode(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT),MAIN_WINDOW_NAME,sf::Style::Titlebar);
    window.setFramerateLimit(MAX_FPS);

    // Here, the window icon is created and established
    sf::Image icon;
    if(!icon.loadFromFile(ICON_FILE_NORMAL))
        printFileError(ICON_FILE_NORMAL);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    logFile << "Loading textures..." << std::endl;
    // All textures are initialized
    TextureHolder textureHolder;
    textureHolder.load(GabrielaTextbox,"sprites/textbox/gabrielaTextbox.png");
    textureHolder.load(DanielaTextbox,"sprites/textbox/danielaTextbox.png");
    textureHolder.load(BystanderTextbox,"sprites/textbox/bystanderTextbox.png");
    textureHolder.load(WarningBackground,"sprites/warning/warningBackground.png");
    textureHolder.load(WarningTitle,"sprites/warning/warningTitle.png");
    textureHolder.load(WarningNormalText,"sprites/warning/warningNormalText.png");
    textureHolder.load(WarningGlitchText,"sprites/warning/warningGlitchText.png");
    textureHolder.load(WarningPressAnyKey,"sprites/warning/warningPressAnyKey.png");
    textureHolder.load(ControlsGabrielaLeftKeyboard,"sprites/controls/controlsGabrielaLeftKeyboard.png");
    textureHolder.load(FloatingLeftKeyboardGabriela,"sprites/controls/floatingLeftKeyboardGabriela.png");

    logFile << "Loading sound effects..." << std::endl;
    // All sound buffers are initialized
    SoundHolder soundHolder;
    soundHolder.load(GabrielaSpeaking,"sounds/speaking/gabrielaSpeaking.wav");
    soundHolder.load(DanielaSpeaking,"sounds/speaking/danielaSpeaking.wav");
    soundHolder.load(Glitch0,"sounds/glitch/glitch0.wav");
    soundHolder.load(Glitch1,"sounds/glitch/glitch1.wav");
    soundHolder.load(AdvanceConversation,"sounds/speaking/advanceConversation.wav");
    soundHolder.load(ControlsGlitchSound,"sounds/glitch/controlsGlitchSound.wav");

    logFile << "Loading music..." << std::endl;
    // Al music themes are initialized
    musicPlayer.load(WarningMusic,"music/warning/warningMusic.wav");

    logFile << "Loading fonts..." << std::endl;
    // All fonts are initialized
    FontHolder fontHolder;
    fontHolder.load(GabrielaFont,"fonts/gabriela.ttf");
    fontHolder.load(DanielaFont,"fonts/daniela.ttf");

    logFile << "Loading conversations..." << std::endl << std::endl;
    // All conversations are initialized
    ConversationHolder conversationHolder(soundHolder);
    conversationHolder.load("files/Conversations.txt");

    // The warning window is created using a pointer to the main window
    WarningWindow ww(&window,textureHolder,soundHolder);

    // The controls window is created with a pointer to the main window
    // as well (this main window will always be used)
    ControlsManager controlsManager(&window,&textureHolder,soundHolder);

    // Then, the warning window runs. If you press ñ (or semicolon)
    // the conversation test will start
    if(ww.run()){
        window.close();
        conversationTest(textureHolder,soundHolder,fontHolder,conversationHolder);
    }

    // The controls for Gabriela are shown
    controlsManager.showControls(GABRIELA);

    return EXIT_SUCCESS;
}
