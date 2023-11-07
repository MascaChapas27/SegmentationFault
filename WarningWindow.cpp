#include "WarningWindow.hpp"

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

    // The texture for the background is set to repeat itself, then
    // it's assigned to the background sprite (possible because
    // it's a reference)
    sf::Texture& auxTexture = textureHolder->get(WarningBackground);
    auxTexture.setRepeated(true);
    backgroundSprite.setTexture(auxTexture);

    // The background is augmented so that it's a giant rectangle
    // full of the same tile
    sf::IntRect backgroundRect = sf::IntRect(0,0,MAIN_WINDOW_WIDTH+WARNING_BACKGROUND_WIDTH,MAIN_WINDOW_HEIGHT+WARNING_BACKGROUND_HEIGHT);
    backgroundSprite.setTextureRect(backgroundRect);

    // The normal text and the title text are set as usual
    normalTextSprite.setTexture(textureHolder->get(WarningNormalText));
    warningTitleSprite.setTexture(textureHolder->get(WarningTitle));

    // The title is positioned according to the value stored in Utilities
    warningTitleSprite.setPosition(WARNING_TITLE_INITIAL_POSITION);

    // The glitch text is assigned a texture and is positioned properly
    glitchTextSprite.setTexture(textureHolder->get(WarningGlitchText));
    sf::IntRect auxRect = glitchTextSprite.getTextureRect();
    auxRect.height = WARNING_GLITCH_HEIGHT;
    glitchTextSprite.setTextureRect(auxRect);
    glitchTextSprite.setPosition(0,WARNING_GLITCH_Y);

    // The sprite for the Press Enter text is set normally
    pressAnyKeySprite.setTexture(textureHolder->get(WarningPressAnyKey));

    // The glitch text sound is initialized
    glitchSound.setBuffer(soundHolder->get(Glitch0));
}

bool WarningWindow::run()
{
    // First of all, the music plays
    MusicPlayer * musicPlayer = MusicPlayer::getInstance();
    musicPlayer->play(WarningMusic);

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
        while(window.pollEvent(event));

        warningTitleTransparency+=3;
        warningTitleSprite.setColor(sf::Color(255,255,255,warningTitleTransparency > 255 ? 255 : warningTitleTransparency));

        window.clear();
        window.draw(warningTitleSprite);
        window.display();
    }

    // Second thing: The "WARNING" title goes up and the background begins to be visible
    int backgroundTransparency = 0;

    while(abs(warningTitleSprite.getPosition().y - WARNING_TITLE_FINAL_POSITION.y) > 3){

            sf::Event event;
            while(window.pollEvent(event));

            backgroundTransparency+=1;
            backgroundSprite.setColor(sf::Color(255,255,255,backgroundTransparency > 255 ? 255 : backgroundTransparency));

            sf::Vector2f movement = WARNING_TITLE_FINAL_POSITION-warningTitleSprite.getPosition();
            movement = sf::Vector2f(movement.x/30.0, movement.y/30.0);

            // The background moves to the left and up until it loops back and starts over,
            // making it look like it's endless
            backgroundSprite.move(-((float)WARNING_BACKGROUND_WIDTH/(float)WARNING_BACKGROUND_HEIGHT)/10.f,-1/10.f);
            if(backgroundSprite.getPosition().x < -WARNING_BACKGROUND_WIDTH)
            {
                backgroundSprite.setPosition(0,0);
            }

            warningTitleSprite.move(movement);

            window.clear();
            window.draw(backgroundSprite);
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
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == DEBUG_KEY) debugMode = true;
                exiting = true;
            }
        }

        if(exiting){
            if(bigBlackRectangle.getFillColor().a < 255)
                bigBlackRectangle.setFillColor(sf::Color(0,0,0,bigBlackRectangle.getFillColor().a+5));
            if(musicPlayer->getVolume() > 1)
                musicPlayer->alterVolume(-1);
            else{
                musicPlayer->stop();
                return debugMode;
            }
        }

        backgroundTransparency+=1;
        backgroundSprite.setColor(sf::Color(255,255,255,backgroundTransparency > 255 ? 255 : backgroundTransparency));

        // The background moves to the left and up until it loops back and starts over,
        // making it look like it's endless
        backgroundSprite.move(-((float)WARNING_BACKGROUND_WIDTH/(float)WARNING_BACKGROUND_HEIGHT)/10.f,-1/10.f);
        if(backgroundSprite.getPosition().x < -WARNING_BACKGROUND_WIDTH)
        {
            backgroundSprite.setPosition(0,0);
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

        // The window is cleared and all sprites are drawn. Then, everything is displayed
        window.clear();
        window.draw(backgroundSprite);
        window.draw(warningTitleSprite);
        window.draw(normalTextSprite);
        window.draw(glitchTextSprite);
        window.draw(pressAnyKeySprite);
        window.draw(bigBlackRectangle);
        window.display();
    }

    musicPlayer->stop();
    return debugMode;
}
