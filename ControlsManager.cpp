#include "ControlsManager.hpp"

ControlsManager::ControlsManager(sf::RenderWindow * window, TextureHolder& textureHolder, SoundHolder& soundHolder)
{
    this->window = window;

    this->controlsSprite.setTexture(textureHolder.get(ControlsGabriela));
    this->controlsSprite.setTextureRect(sf::IntRect(0,0,MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));

    this->glitchSound.setBuffer(soundHolder.get(ControlsGlitchSound));

}

bool ControlsManager::isAvailable(Control c){
    for(std::pair<const CharName, Control> pair : characterControls){
        if(pair.second == c) return false;
    }
    return true;
}

void ControlsManager::showControls(CharName character)
{
    // The sound is played once at the beginning
    glitchSound.play();

    // Counter for the glitch effect that happens when the window
    // is created
    int glitchCounter = 0;

    // The first available control is assigned to the character

    for(int control = KEYBOARD_LEFT; control <= JOYSTICK7; control++){
        if(isAvailable(static_cast<Control>(control))){
            characterControls[character] = static_cast<Control>(control);
        }
    }

    while(true)
    {

        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == GABRIELA_INTERACT)
            {
                return;
            }
        }

        sf::IntRect glitchRect = controlsSprite.getTextureRect();

        // While the glitchCounter is small, the controls window is glitchy
        if(glitchCounter<15)
        {
            // The position of the x axis of the texture is set to a position so that
            // only a glitch part is seen
            glitchRect.left = rand()%(CONTROLS_TEXTURE_WIDTH-MAIN_WINDOW_WIDTH*2);
            glitchCounter++;
        } else {
            // The position of the x axis is set to the rightmost possible position
            glitchRect.left = CONTROLS_TEXTURE_WIDTH-MAIN_WINDOW_WIDTH;
            glitchSound.stop();
        }

        controlsSprite.setTextureRect( glitchRect );

        window->clear();

        window->draw(controlsSprite);

        window->display();
    }
}
