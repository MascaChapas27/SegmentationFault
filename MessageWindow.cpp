#include "MessageWindow.hpp"

// Windows-specific implementation
#ifdef _WIN32

#include <windows.h>

wchar_t* stringToWChar(std::string text)
{
    size_t size = text.length() + 1;
    char classic_string[size];

    for(unsigned int i=0;i<text.length();i++)
        classic_string[i]=text[i];
    classic_string[size-1] = '\0';

    wchar_t* wa = new wchar_t[size];
    mbstowcs(wa,classic_string,size);
    return wa;
}

void MessageWindow::show(std::string title, std::string subtitle){
    MessageBoxW(NULL,stringToWChar(title),stringToWChar(subtitle),MB_ICONERROR | MB_OK);
}

#endif
