#include "Utilities.hpp"
#include "ResourceHolder.hpp"
#include "ConversationHolder.hpp"
#include "MusicPlayer.hpp"
#include "WarningWindow.hpp"
#include "ControlsManager.hpp"

// If you are using Windows, a Windows Factory will be created,
// but if you are using Linux, a Linux Factory will be created.
// These factories create stuff specific to an operating system

#ifdef _WIN32

#include "WindowsFactory.hpp"

AbstractFactory * abstractFactory = new WindowsFactory();

#elif __linux__

#include "LinuxFactory.hpp"

AbstractFactory * abstractFactory = new LinuxFactory();

#endif

// Only definition of the global variables
std::ofstream logFile;
sf::RenderWindow window;

// Debug mode to check if conversations are correct
void conversationTest(ConversationHolder& conversationHolder){
    int code = 0;
    std::cout << "Welcome to conversation debug mode!" << std::endl;

    while(true){
        std::cout << "Enter a conversation code (or -1 to end): ";
        std::cin >> code;

        if(code == -1) break;

        conversationHolder.start(code);

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

    // This is the main window we are going to use through the whole game
    window.create(sf::VideoMode(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT),MAIN_WINDOW_NAME,sf::Style::Titlebar);
    window.setFramerateLimit(MAX_FPS);

    // Here, the window icon is created and established
    sf::Image icon;
    if(!icon.loadFromFile(ICON_FILE_NORMAL))
        printFileError(ICON_FILE_NORMAL);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    logFile << "Loading textures..." << std::endl;
    // All textures are initialized
    TextureHolder * textureHolder = TextureHolder::getTextureInstance();
    textureHolder->load(GabrielaTextbox,"sprites/textbox/gabrielaTextbox.png");
    textureHolder->load(DanielaTextbox,"sprites/textbox/danielaTextbox.png");
    textureHolder->load(BystanderTextbox,"sprites/textbox/bystanderTextbox.png");
    textureHolder->load(WarningBackground,"sprites/warning/warningBackground.png");
    textureHolder->load(WarningTitle,"sprites/warning/warningTitle.png");
    textureHolder->load(WarningNormalText,"sprites/warning/warningNormalText.png");
    textureHolder->load(WarningGlitchText,"sprites/warning/warningGlitchText.png");
    textureHolder->load(WarningPressAnyKey,"sprites/warning/warningPressAnyKey.png");
    textureHolder->load(ControlsGabrielaLeftKeyboard,"sprites/controls/controlsGabrielaLeftKeyboard.png");
    textureHolder->load(FloatingLeftKeyboardGabriela,"sprites/controls/floatingLeftKeyboardGabriela.png");

    logFile << "Loading sound effects..." << std::endl;
    // All sound buffers are initialized
    SoundHolder * soundHolder = SoundHolder::getSoundInstance();
    soundHolder->load(GabrielaSpeaking,"sounds/speaking/gabrielaSpeaking.wav");
    soundHolder->load(DanielaSpeaking,"sounds/speaking/danielaSpeaking.wav");
    soundHolder->load(Glitch0,"sounds/glitch/glitch0.wav");
    soundHolder->load(Glitch1,"sounds/glitch/glitch1.wav");
    soundHolder->load(AdvanceConversation,"sounds/speaking/advanceConversation.wav");
    soundHolder->load(ControlsGlitchSound,"sounds/glitch/controlsGlitchSound.wav");

    logFile << "Loading music..." << std::endl;
    // Al music themes are initialized
    MusicPlayer * musicPlayer = MusicPlayer::getInstance();
    musicPlayer->load(WarningMusic,"music/warning/warningMusic.wav");

    logFile << "Loading fonts..." << std::endl;
    // All fonts are initialized
    FontHolder * fontHolder = FontHolder::getFontInstance();
    fontHolder->load(GabrielaFont,"fonts/gabriela.ttf");
    fontHolder->load(DanielaFont,"fonts/daniela.ttf");

    logFile << "Loading conversations..." << std::endl << std::endl;
    // All conversations are initialized
    ConversationHolder conversationHolder;
    conversationHolder.load("files/Conversations.txt");

    // Then, the warning window runs. If you press ñ (or semicolon
    // (or ` (or whatever just try))) the conversation test will start
    if(WarningWindow::getInstance()->run()){
        window.close();
        conversationTest(conversationHolder);
    }

    // Create a window just to try
    abstractFactory->createWindow("amai","amailakuki");

    // The controls for Gabriela are shown
    ControlsManager::getInstance()->showControls(GABRIELA);

    // Delete the abstract factory
    delete abstractFactory;

    // The end
    return EXIT_SUCCESS;
}
