#include "Textbox.hpp"

void printFileError(std::string fileName){
    std::cerr << "Error: tried to access the file ";
    std::cerr << fileName;
    std::cerr << ", but it wasn't possible" << std::endl;
    exit(1);
}
