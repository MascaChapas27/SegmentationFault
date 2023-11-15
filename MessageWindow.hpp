#ifndef __MESSAGE_WINDOW_HPP__
#define __MESSAGE_WINDOW_HPP__

#include <SFML/System.hpp>
#include <string>

class MessageWindow{
    private:
        // Don't create instances
        MessageWindow();
    public:
        static void show(std::string title, std::string subtitle);
};

#endif // __MESSAGE_WINDOW_HPP__
