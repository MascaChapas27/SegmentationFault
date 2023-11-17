#include <assert.h>
#include "Log.hpp"

// Singleton static variables are initialized as null
template <class Resource, class Identifier>
TextureHolder * ResourceHolder<Resource,Identifier>::textureHolder = nullptr;

template <class Resource, class Identifier>
SoundHolder * ResourceHolder<Resource,Identifier>::soundHolder = nullptr;

template <class Resource, class Identifier>
FontHolder * ResourceHolder<Resource,Identifier>::fontHolder = nullptr;

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::load(Identifier id, const std::string& fileName){
    // Unique pointers are better because they delete themselves when
    // they go out of scope
    std::unique_ptr<Resource> resource(new Resource());

    // We try to load the resource. If there is an error, we log it and die horribly
    if(!resource->loadFromFile(fileName)){
        Log::getInstance()->write("Tried to load " + fileName + " but it went catastrophically bad :(");
        Log::getInstance()->write("Please check that the file is present and check that the name is correct!!");
        exit(EXIT_FAILURE);
    }

    // It's important to std::move the pointer so that it's not destroyed
    // as soon as the function ends.
    resourceMap.insert(std::make_pair(id,std::move(resource)));
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource,Identifier>::get(Identifier id){
    // First we find the element in the map (auto means that the
    // type is automatically infered from the context)
    auto found = resourceMap.find(id);

    // Once we have the element, which is a pair, we return
    // the texture, which is the second element
    return *found -> second;
}

template <class Resource, class Identifier>
TextureHolder * ResourceHolder<Resource,Identifier>::getTextureInstance()
{
    if(textureHolder == nullptr)
        textureHolder = new TextureHolder;
    return textureHolder;
}

template <class Resource, class Identifier>
SoundHolder * ResourceHolder<Resource,Identifier>::getSoundInstance()
{
    if(soundHolder == nullptr)
        soundHolder = new SoundHolder;
    return soundHolder;
}

template <class Resource, class Identifier>
FontHolder * ResourceHolder<Resource,Identifier>::getFontInstance()
{
    if(fontHolder == nullptr)
        fontHolder = new FontHolder;
    return fontHolder;
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllTextures()
{
    load(GabrielaTextbox,"sprites/textbox/gabrielaTextbox.png");
    load(DanielaTextbox,"sprites/textbox/danielaTextbox.png");
    load(BystanderTextbox,"sprites/textbox/bystanderTextbox.png");
    load(WarningBackground,"sprites/warning/warningBackground.png");
    load(WarningTitle,"sprites/warning/warningTitle.png");
    load(WarningNormalText,"sprites/warning/warningNormalText.png");
    load(WarningGlitchText,"sprites/warning/warningGlitchText.png");
    load(WarningPressAnyKey,"sprites/warning/warningPressAnyKey.png");
    load(ControlsGabrielaLeftKeyboard,"sprites/controls/controlsGabrielaLeftKeyboard.png");
    load(FloatingLeftKeyboardGabriela,"sprites/controls/floatingLeftKeyboardGabriela.png");
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllSounds()
{
    load(GabrielaSpeaking,"sounds/speaking/gabrielaSpeaking.wav");
    load(DanielaSpeaking,"sounds/speaking/danielaSpeaking.wav");
    load(Glitch0,"sounds/glitch/glitch0.wav");
    load(Glitch1,"sounds/glitch/glitch1.wav");
    load(AdvanceConversation,"sounds/speaking/advanceConversation.wav");
    load(ControlsGlitchSound,"sounds/glitch/controlsGlitchSound.wav");
}

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::loadAllFonts()
{
    load(GabrielaFont,"fonts/gabriela.ttf");
    load(DanielaFont,"fonts/daniela.ttf");
}
