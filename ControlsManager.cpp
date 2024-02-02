#include "ControlsManager.hpp"

// The instance is initially null
ControlsManager * ControlsManager::controlsManager = nullptr;

ControlsManager * ControlsManager::getInstance()
{
    if(controlsManager == nullptr)
        controlsManager = new ControlsManager;
    return controlsManager;
}

ControlsManager::ControlsManager()
{
    SoundHolder * soundHolder = SoundHolder::getSoundInstance();
    TextureHolder * textureHolder = TextureHolder::getTextureInstance();

    this->glitchSound.setBuffer(soundHolder->get(SoundID::ControlsGlitchSound));

    // Keys for the left part of the keyboard
    associatedKeys[std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::DOWN)] = sf::Keyboard::S;
    associatedKeys[std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::UP)] = sf::Keyboard::W;
    associatedKeys[std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::LEFT)] = sf::Keyboard::A;
    associatedKeys[std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::RIGHT)] = sf::Keyboard::D;
    associatedKeys[std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::INTERACT)] = sf::Keyboard::LShift;
    associatedKeys[std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::EXIT)] = sf::Keyboard::Escape;

    // Buttons for the joysticks (SHOULD BE DELETED AND USE ESC TO EXIT AND ANY BUTTON TO INTERACT)
    associatedButtons[KeyAction::INTERACT] = 0;
    associatedButtons[KeyAction::EXIT] = 6;

    // The background for the floating controls is initialized
    background.setTextureAndNumber(textureHolder->get(TextureID::FloatingLeftKeyboardGabriela),FLOATING_CONTROLS_NUM);
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

// Given a character and a key action, finds whether the character is using
// the keyboard or a controller, and then calls the corresponding function
bool ControlsManager::isPressing(CharName character, KeyAction keyAction){

    // Try to find the character and its control
    auto result = characterControls.find(character);

    // If that character doesn't have a controller assigned, return false
    if(result == characterControls.end()) {
        Log::getInstance()->write("Character doesn't have a control assigned!");
        return false;
    }

    // result is a pair of CharName and Control. If the second element is a keyboard control,
    // then use isPressingKey. If not then it has to be a joystick so use IsPressingButton
    if(result->second == Control::KEYBOARD_LEFT || result->second == Control::KEYBOARD_RIGHT)
        return isPressingKey(character,keyAction);
    else
        return isPressingButton(character,keyAction);

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

    // Only for GABRIELA, check if the game should exit
    if(character == CharName::GABRIELA && keyAction == KeyAction::EXIT)
        return sf::Joystick::isButtonPressed(joystickID,associatedButtons[keyAction]);

    // If it's an INTERACTION action, check the button
    // If it's a movement action, check the joystick's axis position
    switch(keyAction){
    case KeyAction::INTERACT:
        return sf::Joystick::isButtonPressed(joystickID,associatedButtons[keyAction]);

    case KeyAction::LEFT:
        return sf::Joystick::getAxisPosition(joystickID,sf::Joystick::X) < JOYSTICK_AXIS_THRESHOLD;

    case KeyAction::RIGHT:
        return sf::Joystick::getAxisPosition(joystickID,sf::Joystick::X) > JOYSTICK_AXIS_THRESHOLD;

    case KeyAction::UP:
        return sf::Joystick::getAxisPosition(joystickID,sf::Joystick::Y) > JOYSTICK_AXIS_THRESHOLD;

    case KeyAction::DOWN:
        return sf::Joystick::getAxisPosition(joystickID,sf::Joystick::Y) < JOYSTICK_AXIS_THRESHOLD;
    default:
        return false;
    }

}

// Returns true if the character has a control assigned
bool ControlsManager::assignControl(CharName character)
{
    // Check if the character is in the characterControls map
    if(characterControls.find(character) == characterControls.end()){
        // Try to assign a keyboard part
        if(isAvailable(Control::KEYBOARD_LEFT)) characterControls[character] = Control::KEYBOARD_LEFT;
        else if(isAvailable(Control::KEYBOARD_RIGHT)) characterControls[character] = Control::KEYBOARD_RIGHT;

        // If no keyboard part could be assigned, false because the character still doesn't have a control

        else return false;
    }

    // True because the character already has a control
    return true;
}

// Show a character's controls
void ControlsManager::showControls(CharName character)
{
    TextureHolder * textureHolder = TextureHolder::getTextureInstance();

    // The sound is played once at the beginning
    glitchSound.play();

    // Counter for the glitch effect that happens when the window
    // is created
    int glitchCounter = 1;

    // A flag that indicates if the left part of the keyboard and the right part
    // are already in use by other characters, forcing the player to connect a joystick
    bool mustConnectJoystick = !assignControl(character);

    // Depending on the character and the controls, a texture for the controls window is chosen
    switch(character){
        case CharName::GABRIELA:
            if (mustConnectJoystick){
                // this->controlsSprite.setTexture(textureHolder->get(ControlsGabrielaMustConnectJoystick));
            } else if(characterControls[CharName::GABRIELA] == Control::KEYBOARD_LEFT){
                this->controlsSprite.setTexture(textureHolder->get(TextureID::ControlsGabrielaLeftKeyboard));
                //floatingControls[i].setTexture(textureHolder->get(TextureID::FloatingLeftKeyboardGabriela));
                background.setTextureAndNumber(textureHolder->get(TextureID::FloatingLeftKeyboardGabriela),FLOATING_CONTROLS_NUM);
            } else if (characterControls[CharName::GABRIELA] == Control::KEYBOARD_RIGHT){
                // this->controlsSprite.setTexture(textureHolder->get(TextureID::ControlsGabrielaRightKeyboard));
            }

            break;
    }

    // The rectangle for the texture is always the same size (the position changes for the
    // glitch effect)
    this->controlsSprite.setTextureRect(sf::IntRect(0,0,MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT));

    while(glitchCounter != -15)
    {

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(isPressingKey(character,KeyAction::INTERACT) && glitchCounter >= 0){
                    // The sound is played again after pressing the proceed key
                    glitchSound.play();
                    glitchCounter=-1;
                } else if(isPressingKey(CharName::GABRIELA,KeyAction::EXIT))
                    exit(EXIT_SUCCESS);

            } else if(event.type == sf::Event::JoystickButtonPressed)
            {

                // We get the control associated with the joystick whose button was pressed
                Control joystick = static_cast<Control>(event.joystickButton.joystickId+2);

                // If the joystick was unassigned, then it is assigned to the current character
                if(connectJoystick(character,joystick)){
                    glitchCounter = 1;
                    glitchSound.play();
                    mustConnectJoystick = false;
                    // this->controlsSprite.setTexture(textureHolder->get(ControlsGabrielaJoystick));
                } else if(isPressingButton(character,KeyAction::INTERACT) && glitchCounter >= 0) {
                    // The sound is played again after pressing the proceed key
                    glitchSound.play();
                    glitchCounter=-1;
                } else if(isPressingButton(CharName::GABRIELA,KeyAction::EXIT)){
                    exit(EXIT_SUCCESS);
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

        background.update();

        window.clear();

        window.draw(controlsSprite);
        if(glitchCounter==15) window.draw(background);

        window.display();
    }
}
