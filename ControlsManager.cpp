#include "ControlsManager.hpp"

ControlsManager::ControlsManager(sf::RenderWindow * window, TextureHolder& textureHolder, SoundHolder& soundHolder)
{
    this->window = window;

    this->controlsSprite.setTexture(textureHolder.get(ControlsGabriela));
    this->controlsSprite.setTextureRect(sf::IntRect(0,0,MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));

    this->glitchSound.setBuffer(soundHolder.get(ControlsGlitchSound));

    // Keys for the left part of the keyboard
    associatedKeys[std::pair<Control,KeyAction>(KEYBOARD_LEFT,DOWN)] = sf::Keyboard::S;
    associatedKeys[std::pair<Control,KeyAction>(KEYBOARD_LEFT,UP)] = sf::Keyboard::W;
    associatedKeys[std::pair<Control,KeyAction>(KEYBOARD_LEFT,LEFT)] = sf::Keyboard::A;
    associatedKeys[std::pair<Control,KeyAction>(KEYBOARD_LEFT,RIGHT)] = sf::Keyboard::D;
    associatedKeys[std::pair<Control,KeyAction>(KEYBOARD_LEFT,INTERACT)] = sf::Keyboard::LShift;
    associatedKeys[std::pair<Control,KeyAction>(KEYBOARD_LEFT,EXIT)] = sf::Keyboard::Escape;

    // Keys for the joysticks
    associatedButtons[DOWN] = 0;
    associatedButtons[UP] = 0;
    associatedButtons[LEFT] = 0;
    associatedButtons[RIGHT] = 0;
    associatedButtons[INTERACT] = 0;
    associatedButtons[EXIT] = 0;

}

bool ControlsManager::isAvailable(Control c){
    for(std::pair<const CharName, Control> pair : characterControls){
        if(pair.second == c) return false;
    }
    return true;
}

bool ControlsManager::connectJoystick(CharName character, Control joystick){

    // If a joystick is connected when the controls window is showing, then
    // the character will be controlled by the joystick and not the keyboard

    // First we get the joystick value of the enum by getting its ID and adding 2,
    // since the two first elements of the enum are KEYBOARD_LEFT and KEYBOARD_RIGHT,
    // making JOYSTICK0 the third element of the enum

    if(!isAvailable(joystick)) return false;

    characterControls[character] = joystick;
    return true;
}

// Given a character and a key action, it finds the control being used by the character
// (in this case a part of the keyboard) and then checks if the corresponding key is being pressed
bool ControlsManager::isPressingKey(CharName character, KeyAction keyAction){
    // First we use the control associated with the character and the key action to retrieve the key
    std::pair<Control,KeyAction> controlAndKey(characterControls[character], keyAction);

    // Then we check if the key is being pressed
    return sf::Keyboard::isKeyPressed(associatedKeys[controlAndKey]);
}

// Given a character and a key action, it finds the joystick being used and checks if
// the button associated with that key action is being pressed
bool ControlsManager::isPressingButton(CharName character, KeyAction keyAction){
    // First we get the joystick being used by the character
    int joystickID = static_cast<int>(characterControls[character])-2;

    // Then we check if the button is being pressed
    return sf::Joystick::isButtonPressed(joystickID,associatedButtons[keyAction]);
}

void ControlsManager::showControls(CharName character)
{
    // The sound is played once at the beginning
    glitchSound.play();

    // Counter for the glitch effect that happens when the window
    // is created
    int glitchCounter = 1;

    // A flag that indicates if the left part of the keyboard and the right part
    // are already in use by other characters, forcing the player to connect a joystick
    bool mustConnectJoystick = false;

    // The first available control is assigned to the character. The static cast thing allows
    // you to transform an integer into an element of an enum

    if(isAvailable(KEYBOARD_LEFT)) characterControls[character] = KEYBOARD_LEFT;
    else if(isAvailable(KEYBOARD_RIGHT)) characterControls[character] = KEYBOARD_RIGHT;
    else mustConnectJoystick = true;

    while(glitchCounter != -15)
    {

        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && isPressingKey(character,INTERACT) && glitchCounter >= 0)
            {
                // The sound is played again after pressing the proceed key
                glitchSound.play();
                glitchCounter=-1;
            } else if(event.type == sf::Event::JoystickButtonPressed)
            {
                // We get the control associated with the joystick whose button was pressed
                Control joystick = static_cast<Control>(event.joystickButton.joystickId+2);

                // If the joystick was unassigned, then it is assigned to the current character
                if(connectJoystick(character,joystick)){
                    glitchCounter = 1;
                    glitchSound.play();
                } else if(isPressingButton(character,INTERACT) && glitchCounter >= 0) {
                    // The sound is played again after pressing the proceed key
                    glitchSound.play();
                    glitchCounter=-1;
                }

                std::cout << event.joystickButton.button << std::endl;
            }
        }

        sf::IntRect glitchRect = controlsSprite.getTextureRect();

        // While the glitchCounter is small, the controls window is glitchy
        if(glitchCounter<15 && glitchCounter >= 0)
        {
            // The position of the x axis of the texture is set to a position so that
            // only a glitch part is seen
            glitchRect.left = rand()%(CONTROLS_TEXTURE_WIDTH-MAIN_WINDOW_WIDTH*2);
            glitchCounter++;
        } else if(glitchCounter == 15){
            // The position of the x axis is set to the rightmost possible position
            glitchRect.left = CONTROLS_TEXTURE_WIDTH-MAIN_WINDOW_WIDTH;
            glitchSound.stop();
        } else {
            // If we press the proceed key then the glitch counter goes down instead of up
            // until it reaches 15, in which case the run method ends
            glitchRect.left = rand()%(CONTROLS_TEXTURE_WIDTH-MAIN_WINDOW_WIDTH*2);
            glitchCounter--;
        }

        controlsSprite.setTextureRect( glitchRect );

        window->clear();

        window->draw(controlsSprite);

        window->display();
    }
}
