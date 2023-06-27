#include "WarningWindow.hpp"

WarningWindow::WarningWindow(sf::RenderWindow * window, TextureHolder& textureHolder, SoundHolder& soundHolder)
{
    // The window pointer points at the window living in main
    this->window = window;

    // The texture for the background is set to repeat itself, then
    // it's assigned to the background sprite (possible because
    // it's a reference)
    sf::Texture& auxTexture = textureHolder.get(WarningBackground);
    auxTexture.setRepeated(true);
    backgroundSprite.setTexture(auxTexture);

    // The background is augmented so that it's a giant rectangle
    // full of the same tile
    sf::IntRect backgroundRect = sf::IntRect(0,0,MAIN_WINDOW_WIDTH+WARNING_BACKGROUND_WIDTH,MAIN_WINDOW_HEIGHT+WARNING_BACKGROUND_HEIGHT);
    backgroundSprite.setTextureRect(backgroundRect);

    // The normal text is set as usual
    normalTextSprite.setTexture(textureHolder.get(WarningNormalText));

    // The glitch text is assigned a texture and is positioned properly
    glitchTextSprite.setTexture(textureHolder.get(WarningGlitchText));
    sf::IntRect auxRect = glitchTextSprite.getTextureRect();
    auxRect.height = WARNING_GLITCH_HEIGHT;
    glitchTextSprite.setTextureRect(auxRect);
    glitchTextSprite.setPosition(0,WARNING_GLITCH_Y);

    // The sprite for the Press Enter text is set normally
    pressEnterSprite.setTexture(textureHolder.get(WarningPressEnter));

    // The glitch text sound is initialized
    glitchSound.setBuffer(soundHolder.get(Glitch0));
}

void WarningWindow::run()
{
    // This counter starts at a low odd number so that
    // every frame it's added 2 until it reaches 255
    int aux = -199;

    // This boolean helps the Press Enter text become transparent
    // and then opaque infinitely
    bool pressEnterBecomingTransparent = true;

    // The Press Enter sprite begins transparent
    pressEnterSprite.setColor(sf::Color(255,255,255,0));

    while(true)
    {
        // If the user presses Enter, the warning window ends
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return)
            {
                return;
            }
        }

        // The background moves to the right and down until it loops back and starts over,
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
        if(aux>0 && (glitchTextSprite.getTextureRect().top == 0 ? rand()%50 == 11 : rand()%2 == 1))
        {
            glitchTextRect.top = (rand()%3 + 1) * WARNING_GLITCH_HEIGHT;
            glitchSound.play();
        } else {
            glitchTextRect.top = 0;
            glitchSound.stop();
        }
        glitchTextSprite.setTextureRect(glitchTextRect);

        // If we reach the value 255 for the aux counter, the Press Enter text appears
        // and becomes more transparent and then more opaque
        if(aux==255){
            if(pressEnterSprite.getColor().a==0) pressEnterBecomingTransparent = false;
            if(pressEnterSprite.getColor().a==255) pressEnterBecomingTransparent = true;
            int a = pressEnterSprite.getColor().a;
            if(pressEnterBecomingTransparent) pressEnterSprite.setColor(sf::Color(255,255,255,a-5));
            else pressEnterSprite.setColor(sf::Color(255,255,255,a+5));
        }

        // The window is cleared and all sprites are drawn. Then, everything is displayed
        window->clear();

        window->draw(backgroundSprite);
        window->draw(normalTextSprite);
        window->draw(glitchTextSprite);
        window->draw(pressEnterSprite);

        window->display();
    }
}
