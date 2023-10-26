#include "Utilities.hpp"
#include "Textbox.hpp"
#include <SFML/Graphics.hpp>

void printFileError(std::string fileName){
    std::cerr << "Error: tried to access the file ";
    std::cerr << fileName;
    std::cerr << ", but it wasn't possible" << std::endl;
    exit(1);
}

double randDouble(){
    return (rand()%10 + 1) / 10.f + 0.5;
}

void segfault(){
    int * iptr = nullptr;
    *iptr = 11;
}

void checkGraphicsCard(){
    if(sf::Texture::getMaximumSize() < MAX_TEXTURE_SIZE){
        std::cerr << "WARNING!!" << std::endl;
        std::cerr << "It seems like your graphics card is not good enough for this game!! (no offense)" << std::endl;
        std::cerr << "This games uses image files that can be up to " << MAX_TEXTURE_SIZE << " pixels big (length and width), but..." << std::endl;
        std::cerr << "Your graphics card only supports images up to " << sf::Texture::getMaximumSize() << " pixels big!! (bad!!)" << std::endl;
        std::cerr << "I don't think it will work, but who knows?" << std::endl;
        std::cerr << "Do you want to continue at your own risk?? [y/n] (don't worry, nothing bad will happen (unless not being able to play this game is something bad for you (in which case something veeery bad will happen!!)))" << std::endl;

        char yourAnswer;
        std::cin >> yourAnswer;
        int badAnswers = 0;

        while(yourAnswer != 'y'){
            badAnswers++;
            switch(badAnswers){
            case 1:
                std::cerr << "(Please have some hope and enter \"y\")" << std::endl;
                break;
            case 2:
                std::cerr << "Come on!! Just try it!!" << std::endl;
                break;
            case 3:
                std::cerr << "You just have to enter \"y\", is it that hard??" << std::endl;
                break;
            case 4:
                std::cerr << "Please enter \"y\" please please" << std::endl;
                break;
            case 5:
                std::cerr << "Oh my god i'll do it for you" << std::endl;
                std::cerr << "y" << std::endl;
                return;
                break;
            }

            std::cin >> yourAnswer;
        }
    }
}
