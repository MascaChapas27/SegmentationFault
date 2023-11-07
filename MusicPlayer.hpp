#ifndef __MUSIC_PLAYER_HPP__
#define __MUSIC_PLAYER_HPP__

#include <SFML/Audio.hpp>
#include "Utilities.hpp"
#include <string>
#include <map>

// Plays music (no way)
// MusicPlayer is a Singleton
class MusicPlayer
{
    protected:
        MusicPlayer(){}

        static MusicPlayer * musicPlayer;

    private:
        sf::Music currentMusic;
        std::map<MusicID, std::string> filenames;

    public:
        void load(MusicID identifier, const std::string path);
        void play(MusicID theme);
        void stop();
        float getVolume();
        void alterVolume(float change);

        // NEVER COPY A SINGLETON
        MusicPlayer(MusicPlayer &other) = delete;

        // NEVER ASSIGN A SINGLETON
        void operator=(const MusicPlayer &) = delete;

        // Extremeny important static method to get the instance
        static MusicPlayer * getInstance();

};

// The one and only MusicPlayer that will be used in the whole game
extern MusicPlayer musicPlayer;

#endif // __MUSIC_PLAYER_HPP__
