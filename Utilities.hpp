#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/*
    This file contains lots of useful stuff: enums,
    constants, etc etc etc
*/

//////////////////////////////////////////////////////////////////////////////////
//                       GLOBAL VARIABLES?? IN MY CODE??                        //
//////////////////////////////////////////////////////////////////////////////////

// I know global variables are fckuking bad but ehheheh

// The main window
extern sf::RenderWindow window;

//////////////////////////////////////////////////////////////////////////////////
//                                  ENUMERATES                                  //
//////////////////////////////////////////////////////////////////////////////////

// Names for every character in the game and maybe
// something else I forgot
enum class CharName{
    NONE, GABRIELA, DANIELA, PLAYER, BYSTANDER
};

// Identifiers for every texture used
enum class TextureID {
    GabrielaTextbox, DanielaTextbox, BystanderTextbox,
    WarningTitle, WarningBackground, WarningNormalText, WarningGlitchText, WarningPressAnyKey,
    ControlsGabrielaLeftKeyboard,
    FloatingLeftKeyboardGabriela,
    SquareBackground
};

// Identifiers for every font used
enum class FontID {
    GabrielaFont, DanielaFont
};

// Identifiers for every sound effect used
enum class SoundID {
    GabrielaSpeaking, DanielaSpeaking, AdvanceConversation, Glitch0, Glitch1,
    ControlsGlitchSound
};

// Identifiers for every music theme
enum class MusicID {
    WarningMusic
};

// States for a conversation
enum class ConversationState {
    STARTING,           // The up and down rectangles are moving and the background is getting opaque
    HIDING_LEFT_CHAR,   // The character on the left is being hidden
    HIDING_RIGHT_CHAR,  // The character on the right is being hidden
    HIDING_BOTH_CHARS,  // Both characters are being hidden
    SHOWNG_LEFT_CHAR,   // The character on the left is being shown
    SHOWNG_RIGHT_CHAR,  // The character on the right is being shown
    SHOWNG_BOTH_CHARS,  // Both characters are being shown
    SPEAKING,           // There is one character currently speaking
    WAITING,            // Characters are just standing there... menacingly
    ENDING,             // Characters are sent back to hell together with the rectangles and the background
    ENDED               // The conversation ended and the game can continue
};

// Possible controls a character can use
enum class Control{
    KEYBOARD_LEFT, KEYBOARD_RIGHT,
    JOYSTICK0, JOYSTICK1, JOYSTICK2, JOYSTICK3,
    JOYSTICK4, JOYSTICK5, JOYSTICK6, JOYSTICK7
};

// Things a player can do by pressing keys
enum class KeyAction{
    UP, DOWN, LEFT, RIGHT, INTERACT, EXIT, NONE
};

// Directions that a movement can go to
enum class Direction{
    UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT
};

//////////////////////////////////////////////////////////////////////////////////
//                           MISCELLANEOUS CONSTANTS                            //
//////////////////////////////////////////////////////////////////////////////////

// Path in which the log file will be created
const std::string LOG_FILE_PATH = "segfault.log";

// Icons used for the window
const std::string ICON_FILE_NORMAL = "sprites/icons/iconNormal.png";

// Key that you have to press in order to start conversation debug mode
const sf::Keyboard::Key DEBUG_KEY = sf::Keyboard::Semicolon;

// Max and min volume for music
const int MAX_MUSIC_VOLUME = 100;
const int MIN_MUSIC_VOLUME = 0;

// Max sixe of a texture (your graphics card should support it)
const int MAX_TEXTURE_SIZE = 2048;

// Height and width of the main window
const int MAIN_WINDOW_HEIGHT = 600;
const int MAIN_WINDOW_WIDTH = 800;

// Name of the main window
const std::string MAIN_WINDOW_NAME = "amailakuki";

// Max amount of frames per second for the main window
const int MAX_FPS = 60;

//////////////////////////////////////////////////////////////////////////////////
//                           CONVERSATION CONSTANTS                             //
//////////////////////////////////////////////////////////////////////////////////

// Character used to suddenly end an interaction even if the
// player didn't press any button
const char SUDDEN_END_CHAR = '#';

//////////////////////////////////////////////////////////////////////////////////
//                          WARNING WINDOW CONSTANTS                            //
//////////////////////////////////////////////////////////////////////////////////

// Initial and final position of the "WARNING" title
const sf::Vector2f WARNING_TITLE_INITIAL_POSITION = sf::Vector2f(260,268);
const sf::Vector2f WARNING_TITLE_FINAL_POSITION = sf::Vector2f(260,70);

// The height of the glitch text in the warning window
const int WARNING_GLITCH_HEIGHT = 100;

// Position in the Y axis in which the glitch text of
// the warning window should be
const int WARNING_GLITCH_Y = 450;

// Width of the texture for the control window (the left part is
// full of glitch effects)
const int CONTROLS_TEXTURE_WIDTH = MAIN_WINDOW_WIDTH*3;

//////////////////////////////////////////////////////////////////////////////////
//                             CONTROLS CONSTANTS                               //
//////////////////////////////////////////////////////////////////////////////////

// Number of keyboard/joystick symbols that float
// in the background of the controls window
const int FLOATING_CONTROLS_NUM = 10;

// Max speed that the floating controls can reach
// (acts as a positive limit and a negative limit so 3 means 3 and -3)
const int FLOATING_CONTROLS_MAX_SPEED = 1;

// Color for the floating controls (most importantly transparency)
const sf::Color FLOATING_CONTROLS_COLOR = sf::Color(255,255,255,10);

// Some joystick have drift (the joytick isn't moving but
// the control thinks it's moving a bit) so this threshold
// helps with that
const int JOYSTICK_AXIS_THRESHOLD = 30;

// Number of controls (10, which are 2 for the left and right keyboard and 8 for the
// 8 possible joysticks that can be connected with SFML (even though the game only
// allows a maximum of 4 players))
const int NUM_CONTROLS = 10;

// Key that, if it's pressed, makes the game end
const sf::Keyboard::Key EXIT_KEY = sf::Keyboard::Key::Escape;

//////////////////////////////////////////////////////////////////////////////////
//                              UTILITY FUNCTIONS                               //
//////////////////////////////////////////////////////////////////////////////////

// Namespace for functions just in case (inline or else
// it will be defined 19837 times)
namespace util{
    // Returns a random number between a and b
    inline int RandomBetween(int a, int b){
        return a + rand()%(b-a+1);
    }
}


#endif // __UTILITIES_HPP__
