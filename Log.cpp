#include "Log.hpp"
#include "Utilities.hpp"

Log * Log::log = nullptr;

Log * Log::getInstance()
{
    if(log==nullptr)
        log = new Log();
    return log;
}

Log::Log(){
    // Open the file to append (add content at the end)
    logFile.open(LOG_FILE_PATH,std::ios_base::app);

    // Register today's date and write a nice line to separate
    // different logs from different days
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);

    logFile << "----------------------------------------------" << std::endl;
    logFile << "Log File created. Today's date is: " << asctime(ti) << std::endl << std::endl;
}

Log::~Log(){
    logFile.close();
}

void Log::write(std::string stuff)
{
    logFile << stuff << std::endl;
}

void Log::printFileError(std::string fileName){
    logFile << "Error: tried to access the file ";
    logFile << fileName;
    logFile << ", but it wasn't possible" << std::endl;
    exit(EXIT_FAILURE);
}

void Log::checkGraphicsCard(){
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
