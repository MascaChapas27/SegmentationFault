#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
{

}

void MusicPlayer::load(MusicID identifier, const std::string path)
{
    filenames[identifier] = path;
}

void MusicPlayer::play(MusicID theme)
{
    std::string filename = filenames[theme];

    if(!currentMusic.openFromFile(filename))
        printFileError(filename);

    currentMusic.setLoop(true);
    currentMusic.setVolume(MAX_MUSIC_VOLUME);
    currentMusic.play();
}

void MusicPlayer::stop()
{
    currentMusic.stop();
}

float MusicPlayer::getVolume()
{
    return currentMusic.getVolume();
}

void MusicPlayer::alterVolume(float change)
{
    currentMusic.setVolume(currentMusic.getVolume()+change);
}
