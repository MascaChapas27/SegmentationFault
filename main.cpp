#include "Utilities.hpp"
#include "ResourceHolder.hpp"
#include "ConversationHolder.hpp"
#include "MusicPlayer.hpp"
#include "WarningWindow.hpp"
#include "ControlsManager.hpp"
#include "MessageWindow.hpp"
#include "Log.hpp"

// Only definition of the global variables
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

    // Some graphics cards are not good enough for some texture sizes, so let's check it
    Log::getInstance()->checkGraphicsCard();

    // This is the main window we are going to use through the whole game
    window.create(sf::VideoMode(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT),MAIN_WINDOW_NAME,sf::Style::Titlebar);
    window.setFramerateLimit(MAX_FPS);

    // Here, the window icon is created and established
    sf::Image icon;
    if(!icon.loadFromFile(ICON_FILE_NORMAL))
        Log::getInstance()->printFileError(ICON_FILE_NORMAL);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // All textures are initialized
    Log::getInstance()->write("Loading textures...");
    TextureHolder::getTextureInstance()->loadAllTextures();

    // All sound buffers are initialized
    Log::getInstance()->write("Loading sound effects...");
    SoundHolder::getSoundInstance()->loadAllSounds();

    // All songs are initialized
    Log::getInstance()->write("Loading music...");
    MusicPlayer::getInstance()->loadAllMusic();

    // All fonts are initialized
    Log::getInstance()->write("Loading fonts...");
    FontHolder::getFontInstance()->loadAllFonts();

    // All conversations are initialized
    Log::getInstance()->write("Loading conversations...");
    ConversationHolder conversationHolder;
    conversationHolder.load("files/Conversations.txt");

    // Then, the warning window runs. If you press ñ (or semicolon
    // (or ` (or whatever just try))) the conversation test will start
    if(WarningWindow::getInstance()->run()){
        window.close();
        conversationTest(conversationHolder);
    }

    // Create a window just to try
    MessageWindow::show("amai","amailakuki");

    // The controls for Gabriela are shown
    ControlsManager::getInstance()->showControls(GABRIELA);

    // The end
    return EXIT_SUCCESS;
}
