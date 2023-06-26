#include "WarningWindow.hpp"

WarningWindow::WarningWindow(sf::RenderWindow * window, ResourceHolder<sf::Texture,TextureID>& textureHolder)
{
    this->window = window;
    sf::Texture& auxTexture = textureHolder.get(WarningBackground);
    auxTexture.setRepeated(true);
    backgroundSprite.setTexture(auxTexture);
    sf::IntRect backgroundRect = sf::IntRect(0,0,MAIN_WINDOW_WIDTH+WARNING_BACKGROUND_WIDTH,MAIN_WINDOW_HEIGHT+WARNING_BACKGROUND_HEIGHT);
    backgroundSprite.setTextureRect(backgroundRect);

    normalTextSprite.setTexture(textureHolder.get(WarningNormalText));

    glitchTextSprite.setTexture(textureHolder.get(WarningGlitchText));
    sf::IntRect auxRect = glitchTextSprite.getTextureRect();
    auxRect.height = WARNING_GLITCH_HEIGHT;
    glitchTextSprite.setTextureRect(auxRect);
    glitchTextSprite.setPosition(0,WARNING_GLITCH_Y);

    pressEnterSprite.setTexture(textureHolder.get(WarningPressEnter));
}

void WarningWindow::run()
{
    int aux = -199;

    bool pressEnterBecomingTransparent = true;

    pressEnterSprite.setColor(sf::Color(255,255,255,0));

    while(true)
    {
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return)
            {
                return;
            }
        }

        backgroundSprite.move(-((float)WARNING_BACKGROUND_WIDTH/(float)WARNING_BACKGROUND_HEIGHT)/10.f,-1/10.f);
        if(backgroundSprite.getPosition().x < -WARNING_BACKGROUND_WIDTH)
        {
            backgroundSprite.setPosition(0,0);
        }

        if(aux < 255){
            aux+=2;
        }

        normalTextSprite.setColor(sf::Color(255,255,255,aux < 0 ? 0 : aux));
        glitchTextSprite.setColor(sf::Color(255,255,255,aux < 0 ? 0 : aux));

        sf::IntRect glitchTextRect = glitchTextSprite.getTextureRect();

        if(glitchTextSprite.getTextureRect().top == 0 ? rand()%50 == 11 : rand()%2 == 1)
        {
            glitchTextRect.top = (rand()%3 + 1) * WARNING_GLITCH_HEIGHT;
        } else {
            glitchTextRect.top = 0;
        }

        glitchTextSprite.setTextureRect(glitchTextRect);

        if(aux==255){
            if(pressEnterSprite.getColor().a==0) pressEnterBecomingTransparent = false;
            if(pressEnterSprite.getColor().a==255) pressEnterBecomingTransparent = true;
            int a = pressEnterSprite.getColor().a;
            if(pressEnterBecomingTransparent) pressEnterSprite.setColor(sf::Color(255,255,255,a-5));
            else pressEnterSprite.setColor(sf::Color(255,255,255,a+5));
        }

        window->clear();

        window->draw(backgroundSprite);
        window->draw(normalTextSprite);
        window->draw(glitchTextSprite);
        window->draw(pressEnterSprite);

        window->display();
    }
}
