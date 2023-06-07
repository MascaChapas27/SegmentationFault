#include "Textbox.hpp"

// The constructor. It creates a new textbox
Textbox::Textbox(CharName speaker, CharName lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, Position pos){
    // The textbox is initialized without text
    currentText = "";
    finalText = "";

    // The emotion is initialized as 1 (neutral)
    emotion = 1;

    // Very obvious
    this->speaker = speaker;
    this->lookingAt = lookingAt;

    // The text is initialized
    text.setFont(font);
    switch(speaker){
    case GABRIELA:
        text.setFillColor(sf::Color::White);
        break;
    case DANIELA:
        text.setFillColor(sf::Color::Yellow);
        break;
    default:
        break;
    }

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
    posX = position.x;
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
Textbox::Textbox(CharName speaker, CharName lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, Position pos, sf::SoundBuffer& glitchSoundBuffer) :
Textbox(speaker,lookingAt,texture,soundBuffer, font, pos){
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
bool Textbox::update(bool& keyPressed, int target_x, int target_y){

    // If the window is closed, then always return true (that means
    // that at least one character is glitchy and it's doing the final glitch)
    if(!window.isOpen()) return true;

    // Check if the window was manually moved and update posY and posX
    if(window.getPosition().x != posX){
        // If there was a change in the x axis, update
        posX = window.getPosition().x;
        posY = window.getPosition().y;
    } else if(abs(window.getPosition().y-posY) > TEXTBOX_BOUNCE){
        // If there was a change in the y axis, update
        // but ONLY when the position is bigger than the TEXTBOX_BOUNCE
        // because if it's smaller it could be the animation and not
        // manual movement you know
        posX = window.getPosition().x;
        posY = window.getPosition().y;
    }

    // First we check if the conversation should advance
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::KeyPressed && !keyPressed && event.key.code == KEY_OK){
            // Now we are pressing the key, the conversation advances only if
            // the current text is equal to the final text
            keyPressed = true;
            if(currentText == finalText) return true;
            // If not, the text is set to be equal to the final text
            else currentText = finalText;
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
        } else if (!glitchy){
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
        window.requestFocus();
    }

    // The text is always set to the current text
    text.setString(currentText);

    // We check the direction the character is facing
    // Important: the directions start at left and go clockwise,
    // with down-left being the last one. Check the spritesheets at
    // sprites\textbox to see it
    if(target_x > 0){
        if(abs(window.getPosition().y-target_y) < TEXTBOX_TRESSHOLD){
            if(window.getPosition().x > target_x){
                // Look to the left
                faceRect.left = 1 * FACE_WIDTH;
            } else {
                // Look to the right
                faceRect.left = 5 * FACE_WIDTH;
            }
        } else if (abs(window.getPosition().x-target_x) < TEXTBOX_TRESSHOLD){
            if(window.getPosition().y > target_y){
                // Look up
                faceRect.left = 3 * FACE_WIDTH;
            } else {
                // Look down
                faceRect.left = 7 * FACE_WIDTH;
            }
        } else {
            // Diagonal directions
            if(window.getPosition().y > target_y){
                if(window.getPosition().x > target_x){
                    // Look up and to the left
                    faceRect.left = 2 * FACE_WIDTH;
                } else {
                    // Look up and to the right
                    faceRect.left = 4 * FACE_WIDTH;
                }
            } else {
                if(window.getPosition().x > target_x){
                    // Look down and to the left
                    faceRect.left = 8 * FACE_WIDTH;
                } else {
                    // Look down and to the right
                    faceRect.left = 6 * FACE_WIDTH;
                }
            }
        }
    }

    // If the character is glitchy, things can happen
    if(glitchy){
        // If the character is calm there is a chance it starts
        // glitching. If it's glitching, there is a higher chance
        // that another glitch effect comes immediately after.
        if(finalGlitch > 0 || (faceRect.top!=TEXTBOX_HEIGHT ? rand()%50 == 11 : rand()%2 == 1)){
            // The character glitches, as well as the textbox
            // The first row, just under the textbox sprite, is the glitch row
            faceRect.top = TEXTBOX_HEIGHT;
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

            // To avoid errors, if the current text is empty, turn it into
            // one space
            if(currentText == ""){
                currentText = " ";
                finalText = " ";
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
                setEmotion(emotion);
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

void Textbox::setLookingAt(CharName lookingAt){
    this->lookingAt = lookingAt;
}

void Textbox::setEmotion(int emotion){
    this->emotion = emotion;
    faceRect.top = TEXTBOX_HEIGHT + emotion * FACE_HEIGHT;
}

CharName Textbox::getSpeaker(){
    return speaker;
}

CharName Textbox::getLookingAt(){
    return lookingAt;
}

int Textbox::getX(){
    return window.getPosition().x;
}

int Textbox::getY(){
    return window.getPosition().y;
}

Textbox::~Textbox(){

}
