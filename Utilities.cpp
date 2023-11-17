#include "Utilities.hpp"
#include "Textbox.hpp"
#include <SFML/Graphics.hpp>

void segfault(){
    int * iptr = nullptr;
    *iptr = 11;
}
