#include "Interaction.hpp"

Interaction::Interaction(std::string phrase, CharName speaker, CharName listener){
    this->phrase = phrase;
    this->speaker = speaker;
    this->listener = listener;
}

std::string Interaction::getPhrase(){
    return phrase;
}

CharName Interaction::getSpeaker(){
    return speaker;
}

CharName Interaction::getListener(){
    return listener;
}

void Interaction::setPhrase(std::string phrase){
    this->phrase = phrase;
}

void Interaction::setSpeaker(CharName speaker){
    this->speaker = speaker;
}

void Interaction::setListener(CharName listener){
    this->listener = listener;
}

Interaction::~Interaction(){

}
