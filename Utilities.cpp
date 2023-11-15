#include "Utilities.hpp"
#include "Textbox.hpp"
#include <SFML/Graphics.hpp>

double randDouble(){
    return (rand()%10 + 1) / 10.f + 0.5;
}

void segfault(){
    int * iptr = nullptr;
    *iptr = 11;
}
