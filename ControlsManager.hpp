#ifndef __CONTROLS_WINDOW_HPP__
#define __CONTROLS_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include <map>
#include <vector>
#include "FloatingBackground.hpp"

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

        // Map that stores, for each control, the character associated with it
        std::map<Control, CharName> controlToCharacter;

        // Background with floating controls
        FloatingBackground background;

        // Map that stores, for each valid key (except for the exit key), the part of the keyboard and action associated
        std::map<sf::Keyboard::Key,std::pair<Control,KeyAction>> keyToControlAndAction;

        // Function that indicates if a control is free
        bool isAvailable(Control c);

        // Helper functions for the isPressing function
        bool isPressingKey(CharName character, KeyAction keyAction);
        bool isPressingButton(CharName character, KeyAction keyAction);

        // Assign a joystick to a character
        bool connectJoystick(CharName character, Control joystick);

    public:

        // Check if the character is performing that keyAction
        bool isPressing(CharName character, KeyAction keyAction);

        // Check if the character is performing that keyAction but given an event
        bool isPressingEvent(CharName character, KeyAction keyAction, sf::Event event);

        // Given an event, returns the character and the key action associated
        std::pair<CharName,KeyAction> checkEvent(sf::Event event);

        // Automatically tries to assign a keyboard control to a character
        // if that character doesn't have a control assigned
        bool assignControl(CharName character);

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
