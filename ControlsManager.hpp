#ifndef __CONTROLS_WINDOW_HPP__
#define __CONTROLS_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include <map>
#include <vector>

// Class that manages everything related to controls
class ControlsManager
{
    private:
        // Window in which the controls are shown (it's a pointer
        // because the window lives in the main function, we are
        // just going to store a reference to it)
        sf::RenderWindow * window;

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

        // Pointer to the texture holder so that it can be used later
        TextureHolder* textureHolder;

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
        ControlsManager(sf::RenderWindow * window, TextureHolder* textureHolder, SoundHolder& soundHolder);
        bool isPressingKey(CharName character, KeyAction keyAction);
        bool isPressingButton(CharName character, KeyAction keyAction);
        bool connectJoystick(CharName character, Control joystick);
        void showControls(CharName character);
};

#endif // __CONTROLS_WINDOW_HPP__
