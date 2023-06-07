#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <iostream>
#include <SFML/Window.hpp>

/*
    This file contains lots of useful stuff: enums,
    constants, etc etc etc
*/

// Names for every character in the game and maybe
// something else I forgot
enum CharName{
    GABRIELA, DANIELA, PLAYER, BYSTANDER
};

// Identifiers for every texture used
enum TextureID {
    GabrielaTextbox, DanielaTextbox, BystanderTextbox
};

// Identifiers for every font used
enum FontID {
    Gabriela, Daniela
};

// Identifiers for every sound effect used
enum SoundID {
    GabrielaSpeaking, DanielaSpeaking, AdvanceConversation, Glitch0, Glitch1
};

// Positions of a textbox
enum Position {
    TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};

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
const int TEXTBOX_TRESSHOLD = 80;

/* FUNCTIONS */

// Function that inputs an error message whenever a file cannot
// be accessed (it also exits with error code 1)
void printFileError(std::string fileName);

// Function that generates a kind-of random double
// The doubles generated are in the range (0.6, 0.7, ..., 1.4, 1.5)
// because it's used for the pitch of voices and sfx
double randDouble();

// Causes a Segmentation Fault
void segfault();

#endif // __UTILITIES_HPP__
