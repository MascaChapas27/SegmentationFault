#include "Textbox.hpp"

// Helper function that just returns a random double in the range ([0.6,1.5])
double randPitch(){
    return (rand()%10 + 1) / 10.f + 0.5;
}

// The constructor. It creates a new textbox
Textbox::Textbox(CharName speaker, CharName lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, TextboxPosition pos){
    // The textbox is initialized without text
    currentText = "";
    finalText = "";

    // The emotion is initialized as 1 (neutral)
    emotion = 1;

    // The speaker and the lookingAt are initialized
    this->speaker = speaker;
    this->lookingAt = lookingAt;

    // The bounceCounter is set to 0
    bounceCounter = 0;

    // The text is initialized
    text.setFont(font);
    switch(speaker){
    case CharName::GABRIELA:
        text.setFillColor(sf::Color::White);
        break;
    case CharName::DANIELA:
        text.setFillColor(sf::Color::Yellow);
        break;
    case CharName::BYSTANDER:
        break;
    case CharName::PLAYER:
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
    window.create(sf::VideoMode(TEXTBOX_WIDTH, TEXTBOX_HEIGHT), "Textbox", sf::Style::Titlebar);
    window.setFramerateLimit(TEXTBOX_FPS);
    sf::Vector2i position(sf::VideoMode::getDesktopMode().width / 10, sf::VideoMode::getDesktopMode().height / 10);
    switch(pos){
    case TextboxPosition::TOP_RIGHT:
        position.x += sf::VideoMode::getDesktopMode().width / 2;
        break;
    case TextboxPosition::BOTTOM_LEFT:
        position.y += sf::VideoMode::getDesktopMode().height / 2;
        break;
    case TextboxPosition::BOTTOM_RIGHT:
        position.x += sf::VideoMode::getDesktopMode().width / 2;
        position.y += sf::VideoMode::getDesktopMode().height / 2;
        break;
    case TextboxPosition::TOP_LEFT:
        break;
    }

    // The window is set to its corresponding position
    window.setPosition(position);

    // Depending on the name of the character, the window will have a different title
    switch(speaker)
    {
        case CharName::GABRIELA:
            window.setTitle("Gabriela");
            break;
        case CharName::DANIELA:
            window.setTitle("Daniela");
            break;
        case CharName::BYSTANDER:
            window.setTitle("");
            break;
        case CharName::PLAYER:
            break;
    }

    // The rectangles are given values
    backgroundRect = sf::IntRect(0,0,TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    faceRect = sf::IntRect(0,TEXTBOX_HEIGHT+emotion*FACE_HEIGHT,FACE_WIDTH,FACE_HEIGHT);

    // The auxiliar variables are initialized
    glitchy = false;
    finalGlitch = 0;
    shouldEnd = false;
}

// Another constructor if we want the textbox to be glitchy
Textbox::Textbox(CharName speaker, CharName lookingAt, sf::Texture& texture, sf::SoundBuffer& soundBuffer, sf::Font& font, TextboxPosition pos, sf::SoundBuffer& glitchSoundBuffer) :
Textbox(speaker,lookingAt,texture,soundBuffer, font, pos){
    glitchy = true;

    // The glitch sound uses the soundBuffer
    glitchSound.setBuffer(glitchSoundBuffer);
}

// Sets the text the character should say
void Textbox::setText(std::string text){
    currentText = "";
    finalText = text;
    // When the text is set, the bounce
    // counter is increased and the window is
    // moved down a bit (if it's not BYSTANDER)

    bounceCounter=TEXTBOX_BOUNCE;

    // Maybe this should be done with an abstract textbox type but nah
    if(speaker != CharName::BYSTANDER){
        // if the speaker is not bystander then update the y axis position
        sf::Vector2i pos = window.getPosition();
        window.setPosition(pos);
        pos.y+=TEXTBOX_BOUNCE;

        // For some reason I don't understand the fckukucing operating system won't
        // update the position if I just try once so i constantly try until it works
        while(window.getPosition() != pos){
            window.setPosition(pos);
        }
    }
}

// Updates the textbox, making the character look the right way,
// making it speak and drawing the sprites
// True means the conversation related to this textbox must advance
bool Textbox::update(bool checkIfAdvance, int target_x, int target_y){

    // If the window is closed, then always return true (that means
    // that at least one character is glitchy and it's doing the final glitch)
    if(!window.isOpen()) return true;

    // If the checkIfAdvance flag is set to true, then check if the current
    // textbox is ready to advance
    if(checkIfAdvance){
        // If the character said everything it needed to say (and the character
        // was currently speaking, because an empty final text means that the character
        // was not speaking currently) then return true and also specify that the current
        // character is no longer speaking. ALSO: if the character was speaking but their
        // text contained a sudden end char and we press the interact key to skip that text
        // then consider the interaction finished or else the sudden end char will show in the
        // textbox and that's ugly!!1
        if((currentText == finalText && finalText != "") || finalText.find(SUDDEN_END_CHAR) != std::string::npos) {
            currentText = "";
            finalText = "";
            return true;
        }
        // If not, the text is set to be equal to the final text so that it's
        // possible to go through the conversation faster
        else currentText = finalText;
    }


    // Poll events so that the window doesn't get stuck
    sf::Event event;
    while (window.pollEvent(event));
    /*
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
    */

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
    if(bounceCounter > 0) {
        sf::Vector2i pos = window.getPosition();

        // If the speaker isn't BYSTANDER then the textbox
        // is moved up a bit, but if it's BYSTANDER, the textbox moves
        // a bit towards the speaker

        if(speaker!=CharName::BYSTANDER) pos.y -= 1;
        else pos = window.getPosition() + (sf::Vector2i(target_x,target_y) - pos) / 100;
        window.setPosition(pos);
        bounceCounter-=1;
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

        // BYSTANDER talks by using the window's
        // title, so it works differently
        if(speaker == CharName::BYSTANDER){
            window.setTitle(finalText);
            finalText = " ";
            currentText = " ";
        } else {
            // If the sudden end character is found, end immediately
            if(finalText[(int)currentText.length()] == SUDDEN_END_CHAR){
                // Clear the text or else double advance happens idk why
                finalText = "";
                currentText = "";
                return true;
            }
            currentText+=finalText[(int)currentText.length()];
            speakingSound.setPitch(randPitch());
            window.requestFocus();
        }

        // The speaking sound always plays
        speakingSound.play();

    }

    // The text is always set to the current text
    text.setString(currentText);

    // We check the direction the character is facing
    // Important: the directions start at left and go clockwise,
    // with down-left being the last one. Check the spritesheets at
    // sprites\textbox to see it
    if(target_x > 0){
        if(abs(window.getPosition().y-target_y) < TEXTBOX_THRESHOLD){
            if(window.getPosition().x > target_x){
                // Look to the left
                faceRect.left = 1 * FACE_WIDTH;
            } else {
                // Look to the right
                faceRect.left = 5 * FACE_WIDTH;
            }
        } else if (abs(window.getPosition().x-target_x) < TEXTBOX_THRESHOLD){
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
    } else
        // Then the target is the player, so the character
        // must look forward (or the target is nowhere to be seen)
        faceRect.left = 0;

    // If the character is glitchy, things can happen
    if(glitchy){
        // If the character is calm there is a chance it starts
        // glitching. If it's glitching, there is a higher chance
        // that another glitch effect comes immediately after.
        if(finalGlitch > 0 || (faceRect.top!=TEXTBOX_HEIGHT ? rand()%30 == 11 : rand()%2 == 1)){
            // The character glitches, as well as the textbox
            // The first row, just under the textbox sprite, is the glitch row
            faceRect.top = TEXTBOX_HEIGHT;
            faceRect.left = FACE_WIDTH*(rand() % EXPRESSION_NUMBER);
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
            // only if there is text of course
            if(currentText != ""){
                std::string glitchText = currentText;
                for(unsigned int i=0;i<(rand()%currentText.length());i++){
                    // We are going to turn some characters into glitch characters
                    int pos = rand() % glitchText.length();
                    glitchText[pos] = rand()%255;
                }
                text.setString(glitchText);
            }
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

    // If the character is glitchy and the final glitch ended,
    // then close the window
    if(finalGlitch == FINAL_GLITCH_LIMIT) window.close();

    // Finally, false is returned
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
