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

// Each character has 3 different sound effects
// that play every time a new letter is displayed
const int SPEAKING_SOUNDS = 3;

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

// Function that inputs an error message whenever a file cannot
// be accessed (it also exits with error code 1)
void printFileError(std::string fileName);


#endif // __UTILITIES_HPP__
