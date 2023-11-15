#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <fstream>
#include <string>

/*
    This class contains a log that informs about the events
    that happened during the execution of the game
*/

class Log{
    private:

        // The log file
        std::ofstream logFile;

    protected:

        // Don't create instances yourself
        Log();
        ~Log();

        // The only instance
        static Log * log;

    public:

        // Write stuff in the log file ending in \n
        void write(std::string);

        // Write an error related to not being
        // able to find a file and exit
        void printFileError(std::string);

        // Check if the graphics card is correct
        // and write the result
        void checkGraphicsCard();

        // NEVER COPY A SINGLETON
        Log(Log &other) = delete;

        // NEVER ASSIGN A SINGLETON
        void operator=(const Log &) = delete;

        // Extremeny important static method to get the instance
        static Log * getInstance();

};

#endif // __LOG_HPP__
