#ifndef __ABSTRACT_FACTORY_HPP__
#define __ABSTRACT_FACTORY_HPP__

#include <SFML/System.hpp>
#include <string>

class AbstractFactory{
    public:
        virtual ~AbstractFactory(){};
        virtual void createWindow(std::string title, std::string subtitle)=0;
};

#endif // __ABSTRACT_FACTORY_HPP__
