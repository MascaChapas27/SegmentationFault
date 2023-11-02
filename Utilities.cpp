#include "Utilities.hpp"
#include "Textbox.hpp"
#include <SFML/Graphics.hpp>

void printFileError(std::string fileName){
    logFile << "Error: tried to access the file ";
    logFile << fileName;
    logFile << ", but it wasn't possible" << std::endl;
    exit(EXIT_FAILURE);
}

double randDouble(){
    return (rand()%10 + 1) / 10.f + 0.5;
}

void segfault(){
    int * iptr = nullptr;
    *iptr = 11;
}

void checkGraphicsCard(){
    logFile << "Max texture size your graphics can handle: " << sf::Texture::getMaximumSize() << " pixels" << std::endl;
    if(sf::Texture::getMaximumSize() < MAX_TEXTURE_SIZE){
        logFile << "WARNING!!" << std::endl;
        logFile << "It seems like your graphics card is not good enough for this game!! (no offense)" << std::endl;
        logFile << "This games uses image files that can be up to " << MAX_TEXTURE_SIZE << " pixels big (length and width), but..." << std::endl;
        logFile << "Your graphics card only supports images up to " << sf::Texture::getMaximumSize() << " pixels big!! (bad!!)" << std::endl;
        logFile << "I don't think it will work, but who knows?" << std::endl << std::endl;
    }

    if(!sf::Shader::isAvailable()){
        logFile << "It seems like your graphics card doesn't support the use of shaders!!" << std::endl;
        logFile << "This shouldn't be a problem, don't worry (the game will lose some cool effects though...)" << std::endl << std::endl;
    } else {
        logFile << "Your graphics card supports shaders!" << std::endl << std::endl;
    }
}
