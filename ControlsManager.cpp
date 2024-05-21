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

    // Keys, controls and actions for the left part of the keyboard
    keyToControlAndAction[sf::Keyboard::S] = std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::DOWN);
    keyToControlAndAction[sf::Keyboard::W] = std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::UP);
    keyToControlAndAction[sf::Keyboard::A] = std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::LEFT);
    keyToControlAndAction[sf::Keyboard::D] = std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::RIGHT);
    keyToControlAndAction[sf::Keyboard::LShift] = std::pair<Control,KeyAction>(Control::KEYBOARD_LEFT,KeyAction::INTERACT);

    // Keys, controls and actions for the right part of the keyboard
    keyToControlAndAction[sf::Keyboard::I] = std::pair<Control,KeyAction>(Control::KEYBOARD_RIGHT,KeyAction::DOWN);
    keyToControlAndAction[sf::Keyboard::K] = std::pair<Control,KeyAction>(Control::KEYBOARD_RIGHT,KeyAction::UP);
    keyToControlAndAction[sf::Keyboard::J] = std::pair<Control,KeyAction>(Control::KEYBOARD_RIGHT,KeyAction::LEFT);
    keyToControlAndAction[sf::Keyboard::L] = std::pair<Control,KeyAction>(Control::KEYBOARD_RIGHT,KeyAction::RIGHT);
    keyToControlAndAction[sf::Keyboard::Space] = std::pair<Control,KeyAction>(Control::KEYBOARD_RIGHT,KeyAction::INTERACT);

    // The background for the floating controls is initialized
    background.setTextureAndNumber(textureHolder->get(TextureID::FloatingLeftKeyboardGabriela),FLOATING_CONTROLS_NUM);

    // In the beginning every control is associated to NONE
    for(int i=0;i<NUM_CONTROLS;i++){
        controlToCharacter[static_cast<Control>(i)] = CharName::NONE;
    }
}

bool ControlsManager::isAvailable(Control c){
    return controlToCharacter[c] == CharName::NONE;
}

bool ControlsManager::connectJoystick(CharName character, Control joystick){

    // If a joystick button is pressed when the controls window is showing, then
    // the character will be controlled by the joystick and not the keyboard

    if(!isAvailable(joystick)) return false;

    // Unassign the character to its current control
    if(controlToCharacter[Control::KEYBOARD_LEFT] == character){
        controlToCharacter[Control::KEYBOARD_LEFT] = CharName::NONE;
    } else if(controlToCharacter[Control::KEYBOARD_RIGHT] == character){
        controlToCharacter[Control::KEYBOARD_RIGHT] = CharName::NONE;
    }

    controlToCharacter[joystick] = character;
    return true;
}

std::pair<CharName,KeyAction> ControlsManager::checkEvent(sf::Event event)
{
    // This is the pair of CharName and KeyAction that will be returned
    std::pair<CharName,KeyAction> pair(CharName::NONE,KeyAction::NONE);

    if(event.type == sf::Event::JoystickButtonPressed){
        // Someone pressed a key on a joystick, let's find who

        Control control = static_cast<Control>(event.joystickButton.joystickId+2);

        pair.first = controlToCharacter[control];
        if(pair.first != CharName::NONE)
            pair.second = KeyAction::INTERACT;

    } else if (event.type == sf::Event::JoystickMoved){
        // Someone moved a joystick, let's find who

        Control control = static_cast<Control>(event.joystickMove.joystickId+2);

        pair.first = controlToCharacter[control];
        if(pair.first == CharName::NONE)
            pair.second = KeyAction::NONE;
        else{
            // Depending on the axis, do something
            switch(event.joystickMove.axis){
                case sf::Joystick::Axis::PovX:
                case sf::Joystick::Axis::X:
                case sf::Joystick::Axis::R:
                    if(event.joystickMove.position > JOYSTICK_AXIS_THRESHOLD)
                        pair.second = KeyAction::RIGHT;
                    else if(event.joystickMove.position < -JOYSTICK_AXIS_THRESHOLD)
                        pair.second = KeyAction::LEFT;
                    break;
                case sf::Joystick::Axis::PovY:
                case sf::Joystick::Axis::Y:
                case sf::Joystick::Axis::U:
                    if(event.joystickMove.position > JOYSTICK_AXIS_THRESHOLD)
                        pair.second = KeyAction::UP;
                    else if(event.joystickMove.position < -JOYSTICK_AXIS_THRESHOLD)
                        pair.second = KeyAction::DOWN;
                    break;
                default:
                    break;
            }
        }
    } else if (event.type == sf::Event::KeyPressed){
        // Someone pressed a key

        // If it's the exit key, return it immediately
        if(event.key.code == EXIT_KEY)
            pair.second = KeyAction::EXIT;
        else {
            // If it's another key, first check if it's a valid key
            if(keyToControlAndAction.count(event.key.code)){
                // If it is, get the control and the action
                Control c = keyToControlAndAction[event.key.code].first;
                KeyAction ka = keyToControlAndAction[event.key.code].second;

                // Now, assign the CharName and the KeyAction
                pair.first = controlToCharacter[c];
                pair.second = ka;
                // Also check if the character is NONE, in which case the action
                // is also NONE just in case
                if(pair.first == CharName::NONE){
                    pair.second = KeyAction::NONE;
                }
            }
        }
    }

    return pair;
}

/*
// Given a character and a key action, finds whether the character is using
// the keyboard or a controller, and then calls the corresponding function
bool ControlsManager::isPressing(CharName character, KeyAction keyAction){

    // Try to find the character and its control
    auto result = controlToCharacter.find(character);

    // If that character doesn't have a controller assigned, return false
    if(result == controlToCharacter.end()) {
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
    std::pair<Control,KeyAction> controlAndKey(controlToCharacter[character], keyAction);

    // Then we check if the key is being pressed
    return sf::Keyboard::isKeyPressed(associatedKeys[controlAndKey]);
}

// Given a character and a key action, it finds the control being used by the character
// (in this case a part of the keyboard) and then checks if the corresponding key is being pressed
bool ControlsManager::isPressingKeyEvent(CharName character, KeyAction keyAction, sf::Event::KeyEvent keyEvent){
    // First we use the control associated with the character and the key action to retrieve the key
    std::pair<Control,KeyAction> controlAndKey(controlToCharacter[character], keyAction);

    // Then we check if the key is being pressed
    return keyEvent.code == associatedKeys[controlAndKey]);
}

// Given a character and a key action, it finds the joystick being used and checks if
// the button associated with that key action is being pressed
bool ControlsManager::isPressingButton(CharName character, KeyAction keyAction){
    // First we get the joystick being used by the character
    int joystickID = static_cast<int>(controlToCharacter[character])-2;

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

// Given a character and a key action, it finds the joystick being used and checks if
// the button associated with that key action is being pressed
bool ControlsManager::isPressingButtonEvent(CharName character, KeyAction keyAction, sf::Event event){
    // First we get the joystick being used by the character
    int joystickID = static_cast<int>(controlToCharacter[character])-2;

    // Now check if it was a button or an axis

    // We can go to hell soon if the ID is not the correct one
    if(joystickID != event,joystickButton.joystickId)
        return false;

    // Only for GABRIELA, check if the game should exit
    if(character == CharName::GABRIELA && keyAction == KeyAction::EXIT)
        return joystickButton.button == associatedButtons[keyAction];

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

// Given a character, a keyAction and an event, tells whether or not the character is performing that action
bool isPressingEvent(CharName character, KeyAction keyAction, sf::Event event)
{
    // Try to find the character and its control
    auto result = controlToCharacter.find(character);

    // If that character doesn't have a controller assigned, return false
    if(result == controlToCharacter.end()) {
        Log::getInstance()->write("Character doesn't have a control assigned!");
        return false;
    }

    // result is a pair of CharName and Control. If the second element is a keyboard control,
    // then use isPressingKeyEvent. If not then it has to be a joystick so use IsPressingButtonEvent
    if(result->second == Control::KEYBOARD_LEFT || result->second == Control::KEYBOARD_RIGHT)
        return event.type == sf::Event::KeyEvent && isPressingKeyEvent(character,keyAction, event.key.code);
    else
        return (event.type == sf::Event::JoystickButtonEvent || event.type == sf::Event::JoystickMoveEvent) && isPressingButtonEvent(character,keyAction, event.joystickButton);

}
*/

// Returns true if the character has a control assigned by the end of the function (already had one, or didn't
// have un but got a new one). Returns false if the function couldn't assign a control (both parts of the keyboard
// are taken and the player needs to connect a controller)
bool ControlsManager::assignControl(CharName character)
{
    // Is that character already assigned to a control?
    for(int i=0;i<NUM_CONTROLS;i++){
        if(controlToCharacter[static_cast<Control>(i)] == character)
            return true;
    }

    // If you are still here, let's try to assign the character to a keyboard part
    if(controlToCharacter[Control::KEYBOARD_LEFT] == CharName::NONE){
        controlToCharacter[Control::KEYBOARD_LEFT] = character;
        return true;
    } else if(controlToCharacter[Control::KEYBOARD_RIGHT] == CharName::NONE){
        controlToCharacter[Control::KEYBOARD_RIGHT] = character;
        return true;
    }

    // If you reach this point, you have to connect a controller (sorry heheh)
    return false;
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
            } else if(controlToCharacter[Control::KEYBOARD_LEFT] == CharName::GABRIELA){
                this->controlsSprite.setTexture(textureHolder->get(TextureID::ControlsGabrielaLeftKeyboard));
                //floatingControls[i].setTexture(textureHolder->get(TextureID::FloatingLeftKeyboardGabriela));
                background.setTextureAndNumber(textureHolder->get(TextureID::FloatingLeftKeyboardGabriela),FLOATING_CONTROLS_NUM);
            } else if (controlToCharacter[Control::KEYBOARD_RIGHT] == CharName::GABRIELA){
                // this->controlsSprite.setTexture(textureHolder->get(TextureID::ControlsGabrielaRightKeyboard));
            } else {
                // someting something joystick
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
            // Get the character and action given the event
            std::pair<CharName,KeyAction> pair = checkEvent(event);

            // If the action is to exit, then exit, of course
            if(pair.second == KeyAction::EXIT){
                window.close();
                exit(EXIT_SUCCESS);
            }

            // Connect a joystick
            if(pair.first == CharName::NONE && event.type == sf::Event::JoystickButtonPressed){

                // We get the control associated with the joystick whose button was pressed
                Control joystick = static_cast<Control>(event.joystickButton.joystickId+2);

                // If the joystick was unassigned, then it is assigned to the current character
                if(connectJoystick(character,joystick)){
                    glitchCounter = 1;
                    glitchSound.play();
                    mustConnectJoystick = false;
                    // this->controlsSprite.setTexture(textureHolder->get(ControlsGabrielaJoystick));
                }
            }
            // Advance normally
            else if(pair.first == character && pair.second == KeyAction::INTERACT && glitchCounter >= 0){
                glitchSound.play();
                glitchCounter=-1;
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
