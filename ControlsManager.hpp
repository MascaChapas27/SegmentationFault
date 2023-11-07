#ifndef __CONTROLS_WINDOW_HPP__
#define __CONTROLS_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include <map>
#include <vector>

// Class that manages everything related to controls
class ControlsManager
{
    protected:
        ControlsManager();
        static ControlsManager * controlsManager;

    private:
        // Sprite for the image that contains the controls
        sf::Sprite controlsSprite;

        // Glitch sound that plays when the controls window is initialized
        sf::Sound glitchSound;

        // Map that stores, for each character, the control it uses
        std::map<CharName, Control> characterControls;

        // Map that stores, for each keyboard control and action, the key associated with that action
        std::map<std::pair<Control,KeyAction>,sf::Keyboard::Key> associatedKeys;

        // Map that stores, for each action, the joystick button associated with it
        std::map<KeyAction,int> associatedButtons;

        // Function that indicates if a control is free
        bool isAvailable(Control c);

        // Vector of floating symbols of controls that show in the background
        std::vector<sf::Sprite> floatingControls;

        // Vector of speeds for every floating control (this could be done in a separate class)
        std::vector<sf::Vector2f> floatingSpeeds;

        // Function that moves the floating controls in the background
        void moveFloatingControls();

        // Function that draw the floating controls (i swear to god this should
        // be done in a different class but i dont want to make 19048084 classes for
        // silly effects that are going to be used for just one specific situation)
        void drawFloatingControls();

    public:
        // Check if a character is pressing a key on the keyboard
        bool isPressingKey(CharName character, KeyAction keyAction);
        // Check if a character is pressing a fuck dude what the hell
        // I have to change this
        bool isPressingButton(CharName character, KeyAction keyAction);

        // Connect a joystick to a character
        bool connectJoystick(CharName character, Control joystick);

        // Assign a control to a character and show its controls
        void showControls(CharName character);

        // NEVER CLONE A SINGLETON
        ControlsManager(ControlsManager &other) = delete;

        // NEVER ASSIGN A SINGLETON
        void operator=(const ControlsManager &) = delete;

        // Get the instance
        static ControlsManager * getInstance();
};

#endif // __CONTROLS_WINDOW_HPP__
