#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/*
    This file contains lots of useful stuff: enums,
    constants, etc etc etc
*/

////////////////////
//GLOBAL VARIABLES//
////////////////////

// I know global variables are fckuking bad but ehheheh

// Placeholder for the window and the stuffHolders

///////////////////
////// ENUMS //////
///////////////////

// Names for every character in the game and maybe
// something else I forgot
enum CharName{
    GABRIELA, DANIELA, PLAYER, BYSTANDER
};

// Identifiers for every texture used
enum TextureID {
    GabrielaTextbox, DanielaTextbox, BystanderTextbox,
    WarningTitle, WarningBackground, WarningNormalText, WarningGlitchText, WarningPressAnyKey,
    ControlsGabrielaLeftKeyboard,
    FloatingLeftKeyboardGabriela
};

// Identifiers for every font used
enum FontID {
    GabrielaFont, DanielaFont
};

// Identifiers for every sound effect used
enum SoundID {
    GabrielaSpeaking, DanielaSpeaking, AdvanceConversation, Glitch0, Glitch1,
    ControlsGlitchSound
};

// Identifiers for every music theme
enum MusicID {
    WarningMusic
};

// Positions of a textbox
enum TextboxPosition {
    TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

// Possible controls a character can use
enum Control{
    KEYBOARD_LEFT, KEYBOARD_RIGHT,
    JOYSTICK0, JOYSTICK1, JOYSTICK2, JOYSTICK3,
    JOYSTICK4, JOYSTICK5, JOYSTICK6, JOYSTICK7
};

// Things a player can do by pressing keys
enum KeyAction{
    UP, DOWN, LEFT, RIGHT, INTERACT, EXIT
};

///////////////////////
////// CONSTANTS //////
///////////////////////

// Max sixe of a texture (your graphics card should support it)
const int MAX_TEXTURE_SIZE = 2048;

// Height and width of the main window
const int MAIN_WINDOW_HEIGHT = 600;
const int MAIN_WINDOW_WIDTH = 800;

// Height and width of a textbox
const int TEXTBOX_HEIGHT = 200;
const int TEXTBOX_WIDTH = 400;

// Height and width of the face of the characters
// when they are speaking in a textbox
const int FACE_HEIGHT = 180;
const int FACE_WIDTH = 120;

// Size of the textbox border
const int TEXTBOX_BORDER = 10;

// Position in x and y axes of text in a textbox
const int TEXT_X = FACE_WIDTH + 2*TEXTBOX_BORDER + 20;
const int TEXT_Y = TEXTBOX_BORDER + 20;

// Size of the font in textboxes
const int TEXT_SIZE = 20;

// Framerate limit for textboxes
const int TEXTBOX_FPS = 20;

// Total number of textboxes a character has
// (The first one is the basic one, the others are glitchy)
const int TEXTBOX_NUMBER = 3;

// Total number of expression a character has for a certain feeling
// One facing to the front, eight for each direction
// and an extra one for glitch effects
const int EXPRESSION_NUMBER = 10;

// The value at which the final glitch end. A counter starts increasing
// its value until it equals this constant's value
const int FINAL_GLITCH_LIMIT = TEXTBOX_FPS;

// The amount of pixels the screen moves down when advancing
// in a conversation
const int TEXTBOX_BOUNCE = 10;

// The key that should be pressed to accept or interact
const sf::Keyboard::Key KEY_OK = sf::Keyboard::LShift;

// The range of pixels in which a character looks in cardinal directions.
// If the difference in x and y axes is bigger than this tresshold, the
// character will look at a diagonal direction
const int TEXTBOX_THRESHOLD = 80;

// The width and height of the warning background text
const int WARNING_BACKGROUND_WIDTH = 80;
const int WARNING_BACKGROUND_HEIGHT = 30;

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

// Number of keyboard/joystick symbols that float
// in the background of the controls window
const int FLOATING_CONTROLS_NUM = 6;

// Max speed that the floating controls can reach
// (acts as a positive limit and a negative limit so 3 means 3 and -3)
const int FLOATING_CONTROLS_MAX_SPEED = 1;

// Color for the floating controls (most importantly transparency)
const sf::Color FLOATING_CONTROLS_COLOR = sf::Color(255,255,255,10);

// Keys that the left half of the keyboard uses
const sf::Keyboard::Key KL_UP = sf::Keyboard::W;
const sf::Keyboard::Key KL_DOWN = sf::Keyboard::S;
const sf::Keyboard::Key KL_LEFT = sf::Keyboard::A;
const sf::Keyboard::Key KL_RIGHT = sf::Keyboard::D;
const sf::Keyboard::Key KL_INTERACT = sf::Keyboard::LShift;
const sf::Keyboard::Key KL_ESCAPE = sf::Keyboard::Escape;

///////////////////////
////// FUNCTIONS //////
///////////////////////

// Function that inputs an error message whenever a file cannot
// be accessed (it also exits with error code 1)
void printFileError(std::string fileName);

// Function that generates a kind-of random double
// The doubles generated are in the range (0.6, 0.7, ..., 1.4, 1.5)
// because it's used for the pitch of voices and sfx
double randDouble();

// Causes a Segmentation Fault
void segfault();

// Checks if your graphics card is good enough
void checkGraphicsCard();

#endif // __UTILITIES_HPP__
