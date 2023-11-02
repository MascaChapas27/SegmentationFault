#ifndef __MUSIC_PLAYER_HPP__
#define __MUSIC_PLAYER_HPP__

#include <SFML/Audio.hpp>
#include "Utilities.hpp"
#include <string>
#include <map>

class MusicPlayer
{
    private:
        sf::Music currentMusic;
        std::map<MusicID, std::string> filenames;

    public:
        MusicPlayer();
        void load(MusicID identifier, const std::string path);
        void play(MusicID theme);
        void stop();
        float getVolume();
        void alterVolume(float change);
};

// The one and only MusicPlayer that will be used in the whole game
extern MusicPlayer musicPlayer;

#endif // __MUSIC_PLAYER_HPP__
