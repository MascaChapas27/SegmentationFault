#ifndef __TEXTBOX_HPP__
#define __TEXTBOX_HPP__

#include <string>
#include "Utilities.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// This class defines the behavior of textboxes, which are
// windows that contain a picture of a character and some
// text, indicating that the character is speaking
class Textbox{

private:
    // The text appears letter by letter, so this variable stores
    // what part of the text has been said
    std::string currentText;

    // This is the final text that the character should say
    std::string finalText;

    // This is the emotion the character is feeling, which determines
    // the row of sprites it uses from its spritesheet
    int emotion;

    // This stores the character that is currently speaking
    // (See Utilities.hpp for more info on the CharName enum)
    CharName speaker;

    // This indicates who the character is looking at
    CharName lookingAt;

    // This is the window in which the textbox will be displayed
    sf::RenderWindow window;

    // This is the font that the character will use
    sf::Font font;

    // This is the text that will be displayed
    sf::Text text;

    // This is the sprite that will be used to draw the
    // character's face and the background
    sf::Sprite sprite;

    // These are rectangles that represent what portion of the
    // spritesheet is being used. Notice that backgroundRect is
    // meant to represent only the rectangle for the background,
    // which shouldn't change over time. However, faceRect will
    // change all the time as the character uses different faces
    // and looks at different places
    sf::IntRect backgroundRect;
    sf::IntRect faceRect;

    // This is needed to play the speaking sounds
    sf::Sound speakingSound;

    // This is needed to play the glitch sound
    sf::Sound glitchSound;

    // This is needed if we want the textbox to have glitch effects
    bool glitchy;

    // When trying to close a glitched character's window, this counter
    // makes a last glitch effect happen
    int finalGlitch;

    // Boolean value that is set to true if the textbox needs to be closed
    bool shouldEnd;

    // A counter that stores how much the window should move upwards
    // to do the bouce thingy when speaking
    int bounceCounter;

public:
    Textbox(CharName speaker, CharName lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, TextboxPosition pos);
    Textbox(CharName speaker, CharName lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, TextboxPosition pos, sf::SoundBuffer& glitchSoundBuffer);
    ~Textbox();
    void setText(std::string text);
    void setEmotion(int emotion);
    void setLookingAt(CharName lookingAt);
    CharName getSpeaker();
    CharName getLookingAt();
    int getX();
    int getY();
    bool update(bool checkIfAdvance, int target_x, int target_y);
    bool isClosed();
    void end();
};

#endif // __TEXTBOX_HPP__
