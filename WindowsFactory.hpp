// Only for Windows
#ifdef _WIN32

#ifndef __WINDOWS_FACTORY_HPP__
#define __WINDOWS_FACTORY_HPP__

#include "AbstractFactory.hpp"

// This class creates stuff specifically for Windows systems
class WindowsFactory : public AbstractFactory{
    private:
        // I have no idea of what a wchar_t is but I need it
        // to make the message box work
        static wchar_t* stringToWChar(std::string text);

    public:
        WindowsFactory(){}
        void createWindow(std::string title, std::string subtitle);
};

#endif // __WINDOWS_FACTORY_HPP__

#endif
