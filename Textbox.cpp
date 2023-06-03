#include "Textbox.hpp"

// The constructor. It creates a new textbox
Textbox::Textbox(CharName speaker, CharName lookingAt, std::string spritesheetPath, std::string soundFilesPath[3], std::string fontPath, bool glitchy){
    // The textbox is initialized without text
    currentText = "";
    finalText = "";

    // Very obvious
    this->speaker = speaker;
    this->lookingAt = lookingAt;

    // The font is initialized
    if(!font.loadFromFile(fontPath))
        printFileError(fontPath);

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(TEXT_X,TEXT_Y);

    // The spritesheet is initialized
    if(!spritesheet.loadFromFile(spritesheetPath))
        printFileError(spritesheetPath);

    // The sprite uses that spritesheet
    sprite.setTexture(spritesheet);
    sprite.setPosition(TEXTBOX_BORDER,TEXTBOX_BORDER);

    // The speaking sounds are initialized
    for(int i=0;i<SPEAKING_SOUNDS;i++){
        if(!speakingSounds[i].loadFromFile(soundFilesPath[i]))
            printFileError(soundFilesPath[i]);
    }

    // The window is created
    window.create(sf::VideoMode(TEXTBOX_WIDTH, TEXTBOX_HEIGHT), "Textbox");
    window.setFramerateLimit(30);

    // The rectangles are given values
    backgroundRect = sf::IntRect(0,0,TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    faceRect = sf::IntRect(0,TEXTBOX_HEIGHT,FACE_WIDTH,FACE_HEIGHT);

    this->glitchy = glitchy;
}

// Sets the text the character should say
void Textbox::setText(std::string text){
    currentText = "";
    finalText = text;
}

// Updates the textbox, making the character look the right way,
// making it speak and drawing the sprites
bool Textbox::update(){
    // First we clear everything
    window.clear();

    // Then we draw the background
    sprite.setTextureRect(backgroundRect);
    sprite.setPosition(0,0);
    window.draw(sprite);

    // We try to advance one character in the text unless
    // it has been completed
    if(currentText!=finalText){
        currentText+=finalText[(int)currentText.length()];
        sound.setBuffer(speakingSounds[rand()%2]);
        sound.play();
        text.setString(currentText);
    }

    // We check the direction the character is facing
    // TODO check direction

    // If the character is glitchy, then it depends on the
    if(glitchy){
        // If the character is calm there is a chance it starts
        // glitching. If it's glitching, there is a higher chance
        // that another glitch effect comes immediately after.
        // It's important to notice that glitch characters always look
        // at the player (leftmost sprite, faceRect.left==0).
        // Any other sprite is a glitch sprite
        if(faceRect.left==0 ? rand()%30 == 11 : rand()%2 == 1){
            // If the character is calm, there is a chance it glitches
            faceRect.left = FACE_WIDTH*(rand() % 8 + 1);
            // The glitch sfx should be in the last position of the array
            sound.setBuffer(speakingSounds[SPEAKING_SOUNDS-1]);
            sound.play();
            // The textbox moves a bit when it glitches
            sf::Vector2i position = window.getPosition();
            position.x+=rand()%2 + rand()%2 * -1;
            position.y+=rand()%2 + rand()%2 * -1;
            window.setPosition(position);
            // We create a special string based on the current text
            std::string glitchText = currentText;
            for(unsigned int i=0;i<(rand()%currentText.length());i++){
                // We are going to turn some characters into glitch characters
                int pos = rand() % glitchText.length();
                glitchText[pos] = rand()%255;
            }
            text.setString(glitchText);
            window.requestFocus();
        } else {
            // The character is calm again if there is no glitching
            if(faceRect.left != 0){
                faceRect.left = 0;
                text.setString(currentText);
                sound.stop();
            }
        }
    }
    sprite.setTextureRect(faceRect);
    sprite.setPosition(TEXTBOX_BORDER,TEXTBOX_BORDER);

    // We draw the text on the screen
    window.draw(text);

    // Finally we draw the character's face
    window.draw(sprite);

    // Once everything is drawn we display the result
    window.display();

    // Additionally we check if the textbox should be destroyed
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed){
            window.close();
            return false;
        }
    }
    return true;
}

Textbox::~Textbox(){

}
