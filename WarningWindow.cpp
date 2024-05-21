#include "WarningWindow.hpp"
#include "LoopingBackground.hpp"
#include "AbstractBackground.hpp"
#include "FadingBackground.hpp"
#include "RectangleBackground.hpp"
#include "ConversationHolder.hpp"

WarningWindow * WarningWindow::warningWindow = nullptr;

WarningWindow * WarningWindow::getInstance()
{
    if(warningWindow == nullptr)
        warningWindow = new WarningWindow;
    return warningWindow;
}

WarningWindow::WarningWindow()
{
    TextureHolder * textureHolder = TextureHolder::getTextureInstance();
    SoundHolder * soundHolder = SoundHolder::getSoundInstance();

    // Background that ways "warning"
    std::unique_ptr<LoopingBackground> loopingBackground(new LoopingBackground());
    loopingBackground->setTexture(textureHolder->get(TextureID::WarningBackground),Direction::UP_LEFT);

    background.setBackground(std::move(loopingBackground));
    background.setColor(sf::Color(255,255,255,0));
    background.setInitialColor(sf::Color(255,255,255,0));
    background.setFinalColor(sf::Color(255,255,255,255));

    // Foreground that makes everything black

    std::unique_ptr<AbstractBackground> rectangleBackground(new RectangleBackground());

    foreground.setBackground(std::move(rectangleBackground));
    foreground.setColor(sf::Color(0,0,0,0));
    foreground.setInitialColor(sf::Color(0,0,0,0));
    foreground.setFinalColor(sf::Color(0,0,0,255));
    foreground.setFadingSpeed(5);

    // The normal text and the title text are set as usual
    normalTextSprite.setTexture(textureHolder->get(TextureID::WarningNormalText));
    warningTitleSprite.setTexture(textureHolder->get(TextureID::WarningTitle));

    // The title is positioned according to the value stored in Utilities
    warningTitleSprite.setPosition(WARNING_TITLE_INITIAL_POSITION);

    // The glitch text is assigned a texture and is positioned properly
    glitchTextSprite.setTexture(textureHolder->get(TextureID::WarningGlitchText));
    sf::IntRect auxRect = glitchTextSprite.getTextureRect();
    auxRect.height = WARNING_GLITCH_HEIGHT;
    glitchTextSprite.setTextureRect(auxRect);
    glitchTextSprite.setPosition(0,WARNING_GLITCH_Y);

    // The sprite for the Press Enter text is set normally
    pressAnyKeySprite.setTexture(textureHolder->get(TextureID::WarningPressAnyKey));

    // The glitch text sound is initialized
    glitchSound.setBuffer(soundHolder->get(SoundID::Glitch0));
}

bool WarningWindow::run()
{
    // First of all, the music plays
    MusicPlayer * musicPlayer = MusicPlayer::getInstance();
    musicPlayer->play(MusicID::WarningMusic);

    // This counter starts at a low odd number so that
    // every frame it's added 2 until it reaches 255
    int aux = -199;

    // This boolean helps the Press Any Key text become transparent
    // and then opaque infinitely
    bool pressAnyKeyBecomingTransparent = true;

    // The Press Any Key sprite begins transparent
    pressAnyKeySprite.setColor(sf::Color(255,255,255,0));

    // First thing that happens: there is nothing on screen, then the "WARNING" text
    // appears in the middle of the screen

    int warningTitleTransparency = 0;
    while(warningTitleTransparency < 400){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.key.code == EXIT_KEY){
                window.close();
                exit(EXIT_SUCCESS);
            }
        }

        warningTitleTransparency+=3;
        warningTitleSprite.setColor(sf::Color(255,255,255,warningTitleTransparency > 255 ? 255 : warningTitleTransparency));

        window.clear();
        window.draw(warningTitleSprite);
        window.display();
    }

    // Second thing: The "WARNING" title goes up and the background begins to be visible

    while(abs(warningTitleSprite.getPosition().y - WARNING_TITLE_FINAL_POSITION.y) > 3){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.key.code == EXIT_KEY){
                window.close();
                exit(EXIT_SUCCESS);
            }
        }

        sf::Vector2f movement = WARNING_TITLE_FINAL_POSITION-warningTitleSprite.getPosition();
        movement = sf::Vector2f(movement.x/30.0, movement.y/30.0);
        warningTitleSprite.move(movement);

        background.update();

        window.clear();
        window.draw(background);
        window.draw(warningTitleSprite);
        window.display();
    }

    // Third thing: the normal text and the glitch text appears, as well as
    // the "Press Any Key" text, allowing the player to continue

    // This flag is set to true if we press any key
    bool exiting = false;

    // This flag is set to enable debug mode for conversations
    bool debugMode = false;

    // This rectangle will cover the screen and make it completely black at the end
    sf::RectangleShape bigBlackRectangle;
    bigBlackRectangle.setFillColor(sf::Color(0,0,0,0));
    bigBlackRectangle.setPosition(0,0);
    bigBlackRectangle.setSize(sf::Vector2f(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));

    while(true)
    {
        // If the user presses any key, the warning window ends
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.key.code == EXIT_KEY){
                window.close();
                exit(EXIT_SUCCESS);
            }

            if(event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed)
            {
                if(event.key.code == DEBUG_KEY) debugMode = true;
                exiting = true;

                // This is just for debugging please dont look at it too much
                ConversationHolder conversationHolder;
                conversationHolder.load("files/Conversations.txt");
                conversationHolder.start(0);
            }
        }

        if(exiting){
            foreground.update();
            if(musicPlayer->getVolume() > 1)
                musicPlayer->alterVolume(-1);
            else{
                musicPlayer->stop();
                return debugMode;
            }
        }

        // The aux counter increases in 2 until it reaches 255
        if(aux < 255){
            aux+=2;
        }

        // The sprite for the text (both normal and glitch) is updated and its
        // transparency depends on the aux counter (while it's less than 0 the
        // transparency is 0, making it transparent, and then it becomes more
        // and more opaque until it reaches 255)
        normalTextSprite.setColor(sf::Color(255,255,255,aux < 0 ? 0 : aux));
        glitchTextSprite.setColor(sf::Color(255,255,255,aux < 0 ? 0 : aux));

        // Just like with glitch characters and their textbox, the glitch text
        // glitches sometimes. When this happens, a glitch sound plays
        sf::IntRect glitchTextRect = glitchTextSprite.getTextureRect();
        if(!exiting && aux>0 && (glitchTextSprite.getTextureRect().top == 0 ? rand()%50 == 11 : rand()%2 == 1))
        {
            glitchTextRect.top = (rand()%3 + 1) * WARNING_GLITCH_HEIGHT;
            glitchSound.play();
        } else {
            glitchTextRect.top = 0;
            glitchSound.stop();
        }
        glitchTextSprite.setTextureRect(glitchTextRect);

        // If we reach the value 255 for the aux counter, the Press Any Key text appears
        // and becomes more transparent and then more opaque
        if(aux==255){
            if(pressAnyKeySprite.getColor().a==0) pressAnyKeyBecomingTransparent = false;
            if(pressAnyKeySprite.getColor().a==255) pressAnyKeyBecomingTransparent = true;
            int a = pressAnyKeySprite.getColor().a;
            if(pressAnyKeyBecomingTransparent) pressAnyKeySprite.setColor(sf::Color(255,255,255,a-5));
            else pressAnyKeySprite.setColor(sf::Color(255,255,255,a+5));
        }

        background.update();

        // The window is cleared and all sprites are drawn. Then, everything is displayed
        window.clear();
        window.draw(background);
        window.draw(warningTitleSprite);
        window.draw(normalTextSprite);
        window.draw(glitchTextSprite);
        window.draw(pressAnyKeySprite);
        window.draw(foreground);
        window.display();
    }

    musicPlayer->stop();
    return debugMode;
}
