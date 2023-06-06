#include "Textbox.hpp"

// The constructor. It creates a new textbox
Textbox::Textbox(CharName speaker, std::unique_ptr<Textbox> lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, Position pos){
    // The textbox is initialized without text
    currentText = "";
    finalText = "";

    // Very obvious
    this->speaker = speaker;
    this->lookingAt = std::move(lookingAt);

    // The text is initialized
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(TEXT_SIZE);
    text.setPosition(TEXT_X,TEXT_Y);

    // The sprite uses the texture
    sprite.setTexture(texture);
    sprite.setPosition(TEXTBOX_BORDER,TEXTBOX_BORDER);

    // The sound uses the soundBuffer
    speakingSound.setBuffer(soundBuffer);

    // The window is created
    window.create(sf::VideoMode(TEXTBOX_WIDTH, TEXTBOX_HEIGHT), "Textbox", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(TEXTBOX_FPS);
    sf::Vector2i position(sf::VideoMode::getDesktopMode().width / 10, sf::VideoMode::getDesktopMode().height / 10);
    switch(pos){
    case TOP_RIGHT:
        position.x += sf::VideoMode::getDesktopMode().width / 2;
        break;
    case BOTTOM_LEFT:
        position.y += sf::VideoMode::getDesktopMode().height / 2;
        break;
    case BOTTOM_RIGHT:
        position.x += sf::VideoMode::getDesktopMode().width / 2;
        position.y += sf::VideoMode::getDesktopMode().height / 2;
        break;
    default:
        break;
    }

    // The window is set to its corresponding position and the posY
    // is set to its initial value
    posY = position.y;
    window.setPosition(position);

    // The rectangles are given values
    backgroundRect = sf::IntRect(0,0,TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    faceRect = sf::IntRect(0,TEXTBOX_HEIGHT,FACE_WIDTH,FACE_HEIGHT);

    // The auxiliar variables are initialized
    glitchy = false;
    finalGlitch = 0;
    shouldEnd = false;
}

// Another constructor if we want the textbox to be glitchy
Textbox::Textbox(CharName speaker, std::unique_ptr<Textbox> lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, Position pos, sf::SoundBuffer& glitchSoundBuffer) :
Textbox(speaker,std::move(lookingAt),texture,soundBuffer, font, pos){
    glitchy = true;

    // The glitch sound uses the soundBuffer
    glitchSound.setBuffer(glitchSoundBuffer);
}

// Sets the text the character should say
void Textbox::setText(std::string text){
    currentText = "";
    finalText = text;
    // When the text is set, the window moves down a bit
    sf::Vector2i pos = window.getPosition();
    pos.y += TEXTBOX_BOUNCE;
    window.setPosition(pos);
}

// Updates the textbox, making the character look the right way,
// making it speak and drawing the sprites
bool Textbox::update(bool& keyPressed){
    // If the window is closed, then always return true (that means
    // that at least one character is glitchy and it's doint the final glitch
    if(!window.isOpen()) return true;
    // First we check if the conversation should advance
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::KeyPressed && !keyPressed && event.key.code == KEY_OK){
            // Now we are pressing the key, the conversation advances
            keyPressed = true;
            return true;
        } else if (event.type == sf::Event::KeyReleased && keyPressed && event.key.code == KEY_OK){
            // Now the key is being released
            keyPressed = false;
        }
    }

    // If the window should end, do it
    if(shouldEnd){
        if(glitchy && finalGlitch == 0){
            finalGlitch = 1;
            shouldEnd = false;
        } else {
            window.close();
            return true;
        }
    }

    // If the window is lower than it should, put it back in its place slowly
    if(window.getPosition().y > posY) {
        sf::Vector2i pos = window.getPosition();
        pos.y -= 1;
        window.setPosition(pos);
    }

    // If the window is still open, clear everything
    window.clear();

    // Then we draw the background
    sprite.setTextureRect(backgroundRect);
    sprite.setPosition(0,0);
    window.draw(sprite);

    // We try to advance one character in the text unless
    // it has been completed
    if(currentText!=finalText){
        currentText+=finalText[(int)currentText.length()];
        speakingSound.setPitch(randDouble());
        speakingSound.play();
        text.setString(currentText);
        window.requestFocus();
    }

    // We check the direction the character is facing
    // TODO check direction

    // If the character is glitchy, things can happen
    if(glitchy){
        // If the character is calm there is a chance it starts
        // glitching. If it's glitching, there is a higher chance
        // that another glitch effect comes immediately after.
        // It's important to notice that glitch characters always look
        // at the player (leftmost sprite, faceRect.left==0).
        // Any other sprite is a glitch sprite
        if(finalGlitch > 0 || (faceRect.left==0 ? rand()%30 == 11 : rand()%2 == 1)){
            // The character glitches, as well as the textbox
            faceRect.left = FACE_WIDTH*(rand() % (EXPRESSION_NUMBER-1) + 1);
            backgroundRect.left = TEXTBOX_WIDTH*(rand() % (TEXTBOX_NUMBER-1) + 1);
            // A glitch sound is played
            glitchSound.play();

            // If the final glitch is happening, the counter advances until the limit is reached
            // and the window changes position randomly
            if(finalGlitch > 0) {
                finalGlitch++;
                sf::Vector2i pos = window.getPosition();
                pos.x += rand() % finalGlitch - (finalGlitch/2.f);
                pos.y += rand() % finalGlitch - (finalGlitch/2.f);
                window.setPosition(pos);
            }
            // We create a special string based on the current text
            std::string glitchText = currentText;
            for(unsigned int i=0;i<(rand()%currentText.length());i++){
                // We are going to turn some characters into glitch characters
                int pos = rand() % glitchText.length();
                glitchText[pos] = rand()%255;
            }
            text.setString(glitchText);
        } else {
            // The character is calm again if there is no glitching
            if(faceRect.left != 0){
                faceRect.left = 0;
                backgroundRect.left = 0;
                text.setString(currentText);
                glitchSound.stop();
            }
        }
    }
    // The rectangle for the texture is set
    sprite.setTextureRect(faceRect);
    sprite.setPosition(TEXTBOX_BORDER,TEXTBOX_BORDER);

    // We draw the text on the screen
    window.draw(text);

    // Finally we draw the character's face
    window.draw(sprite);

    // Once everything is drawn we display the result
    window.display();

    // Finally, false is returned, and the window is closed if it needs
    if(finalGlitch == FINAL_GLITCH_LIMIT) window.close();
    return false;
}

void Textbox::end(){
    shouldEnd = true;
}

bool Textbox::isClosed(){
    return !window.isOpen();
}

void Textbox::setLookingAt(std::unique_ptr<Textbox> lookingAt){
    this->lookingAt = std::move(lookingAt);
}

CharName Textbox::getSpeaker(){
    return speaker;
}

Textbox::~Textbox(){

}
