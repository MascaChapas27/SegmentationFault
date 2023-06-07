#include "ConversationHolder.hpp"
#include <fstream>

ConversationHolder::ConversationHolder(ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder){
    advanceSound.setBuffer(soundHolder.get(AdvanceConversation));
}

void ConversationHolder::load(std::string path){
    // Open the file
    std::fstream f(path);
    if(!f) printFileError(path);

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
            characters.push_back((CharName)(line[0]-'0'));
        }

        // Now we get the glitched characters
        getline(f,line);
        int glitchChars = line[0]-'0';


        for(int i=0;i<glitchChars;i++){
            getline(f,line);
            glitchCharacters.push_back((CharName)(line[0]-'0'));
        }

        // Now we read info in groups of four
        do {
            Interaction i;
            int speaker;
            int listener;
            int emotion;

            getline(f,line);
            speaker = line[0]-'0';

            getline(f,line);
            listener = line[0]-'0';

            getline(f,line);
            emotion = line[0]-'0';

            std::string phrase;

            i.setSpeaker((CharName)speaker);
            i.setListener((CharName)listener);
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
void ConversationHolder::start(int code, ResourceHolder<sf::Texture,TextureID>& textureHolder,
           ResourceHolder<sf::SoundBuffer,SoundID>& soundHolder,
           ResourceHolder<sf::Font,FontID>& fontHolder){
    currentConversation = code;
    advanceSound.play();
    conversations[code]->initialize(textureHolder,soundHolder,fontHolder);
}

// It updates the current conversation
bool ConversationHolder::updateConversation(){
    if(conversations[currentConversation]->update()) {
        // A sound plays when advancing
        advanceSound.play();
        return conversations[currentConversation]->advance();
    }
    return true;
}

ConversationHolder::~ConversationHolder(){

}
