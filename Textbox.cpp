#include "Textbox.hpp"

// The constructor. It creates a new textbox
Textbox::Textbox(CharName speaker, CharName lookingAt, std::string spritesheetPath, std::string soundFilesPath[3], std::string fontPath){
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
    window.setFramerateLimit(60);

    // The rectangles are given values
    backgroundRect = sf::IntRect(0,0,TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    faceRect = sf::IntRect(0,TEXTBOX_HEIGHT,FACE_WIDTH,FACE_HEIGHT);
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
        sound.setBuffer(speakingSounds[rand()%3]);
        sound.play();
        text.setString(currentText);
    }

    // We draw the text on the screen
    window.draw(text);

    // We check the direction the character is facing
    // TODO check direction
    sprite.setTextureRect(faceRect);
    sprite.setPosition(TEXTBOX_BORDER,TEXTBOX_BORDER);

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
            setText("que haces cerrandome\ncabron te parto las\nputas piernas");
        }
    }
    return true;
}

Textbox::~Textbox(){

}
