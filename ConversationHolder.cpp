#include "ConversationHolder.hpp"
#include "ResourceHolder.hpp"
#include "ControlsManager.hpp"
#include <fstream>
#include "Log.hpp"

ConversationHolder::ConversationHolder(){
    keyPressed = false;
    advanceSound.setBuffer(SoundHolder::getSoundInstance()->get(SoundID::AdvanceConversation));
    names["GABRIELA"] = CharName::GABRIELA;
    names["DANIELA"] = CharName::DANIELA;
    names["BYSTANDER"] = CharName::BYSTANDER;
    names["PLAYER"] = CharName::PLAYER;
}

void ConversationHolder::load(std::string path){
    // Open the file
    std::fstream f(path);
    if(!f) Log::getInstance()->printFileError(path);

    // The auxiliar variables are declared
    std::list<Interaction> interactions;
    std::list<CharName> characters;
    std::list<CharName> glitchCharacters;
    std::string line;
    int code = 0;

    // We get the first line
    getline(f,line);

    // While there are lines in the file...
    while(line[0] != '@'){
        // Ignore comments
        if(line[0]=='#') {
            getline(f,line);
            continue;
        }

        // We assume that the file is properly written
        // and the first thing we find is the number
        // of normal characters
        int normalChars = line[0]-'0';

        for(int i=0;i<normalChars;i++){
            getline(f,line);
            // line.erase(line.size() - 1);
            characters.push_back(names[line]);
        }

        // Now we get the glitched characters
        getline(f,line);
        int glitchChars = line[0]-'0';


        for(int i=0;i<glitchChars;i++){
            getline(f,line);
            // The last character is erased (the \n)
            // line.erase(line.size() - 1);
            glitchCharacters.push_back(names[line]);
        }

        // One blank line that separate info about chars from the conversation
        getline(f,line);

        // Now we read info in groups of four
        do {
            Interaction i;
            std::string speaker;
            std::string listener;
            int emotion;

            getline(f,line);
            speaker = line;

            getline(f,line);
            listener = line;

            getline(f,line);
            emotion = line[0]-'0';

            std::string phrase;

            i.setSpeaker(names[speaker]);
            i.setListener(names[listener]);
            i.setEmotion(emotion);
            getline(f,line);
            while(line != "" && line != "$"){
                phrase += (line+"\n");
                getline(f,line);
            }
            i.setPhrase(phrase);
            interactions.push_back(i);
        } while(line[0] != '$');

        // The conversation is stored in its place
        std::unique_ptr<Conversation> c(new Conversation(interactions,characters,glitchCharacters));
        auto inserted = conversations.insert(std::make_pair(code,std::move(c)));
        assert(inserted.second == true);

        // We clear everything before continuing
        characters.clear();
        glitchCharacters.clear();
        interactions.clear();

        // Of course, the code must be different for the next conversation
        code++;

        // We get the next line
        getline(f,line);
    }
}

// It starts the given conversation
void ConversationHolder::start(int code){

    currentConversation = code;
    advanceSound.play();
    conversations[code]->initialize();
    keyPressed = false;
}

// It updates the current conversation
bool ConversationHolder::updateConversation(){

    bool checkIfAdvance = false;

    // True if the key (or button) iis being pressed exactly at this moment, as opposed to keyPressed, which
    // tells if it was being pressed the last time this function was called. This prevents from pressing
    // the key once and advancing 131233 times unintentionally
    bool pressingRightNow = ControlsManager::getInstance()->isPressing(CharName::GABRIELA,KeyAction::INTERACT);

    if (pressingRightNow && !keyPressed){
        // Now we are pressing the key, the conversation advances only if
        // the current text is equal to the final text, and the current character
        // is speaking (if it's not, then the current text and final text
        // are both empty)
        keyPressed = true;
        checkIfAdvance = true;

        // A sound plays when pressing the key
        advanceSound.play();

    } else if (!pressingRightNow && keyPressed){
        // Now the key is being released
        keyPressed = false;
    }

    if(conversations[currentConversation]->update(checkIfAdvance))
        return conversations[currentConversation]->advance();

    return true;
}

ConversationHolder::~ConversationHolder(){

}
