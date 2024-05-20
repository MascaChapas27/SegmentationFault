#include "Interaction.hpp"

Interaction::Interaction(){

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

int Interaction::getEmotion(){
    return emotion;
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

void Interaction::setEmotion(int emotion){
    this->emotion = emotion;
}

Interaction::~Interaction(){

}
