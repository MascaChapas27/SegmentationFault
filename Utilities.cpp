#include "Textbox.hpp"

void printFileError(std::string fileName){
    std::cerr << "Error: tried to access the file ";
    std::cerr << fileName;
    std::cerr << ", but it wasn't possible" << std::endl;
    exit(1);
}

double randDouble(){
    return (rand()%10 + 1) / 10.f + 0.5;
}
