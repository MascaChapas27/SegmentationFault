#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <iostream>

/*
    This file contains lots of useful stuff: enums,
    constants, etc etc etc
*/

/* RELATING TO THE TEXTBOX */

// Names for every character in the game and maybe
// something else I forgot
enum CharName{
    GABRIELA, DANIELA, FATHER, MOTHER, PLAYER
};

// Identifiers for every texture used
enum TextureID {
    GabrielaTextbox
};

// Identifiers for every sound effect used
enum SoundID {
    GabrielaSpeaking, Glitch0
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

// Function that inputs an error message whenever a file cannot
// be accessed (it also exits with error code 1)
void printFileError(std::string fileName);

// Function that generates a kind-of random double
// The doubles generated are in the range (0.6, 0.7, ..., 1.4, 1.5)
// because it's used for the pitch of voices and sfx
double randDouble();

#endif // __UTILITIES_HPP__
