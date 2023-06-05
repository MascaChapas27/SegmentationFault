#ifndef __RESOURCE_HOLDER__
#define __RESOURCE_HOLDER__

#include "Utilities.hpp"
#include <memory>
#include <map>

/*
    The ResourceHolder is a class that is in charge of resources.
    Instead of loading resources inside of other classes, all resources
    are loaded from the first moment in this class. This ensures that all
    resources are available at all times. This is a generic class, so it can
    be used for textures, fonts and sound buffers without a problem
*/
template <class Resource, class Identifier>
class ResourceHolder
{
    private:
        // A map that contains a resource for each identifier
        std::map<Identifier, std::unique_ptr<Resource>> resourceMap;

    public:
        // Loads a resource given its ID and its path
        void load(Identifier id, const std::string& filename);

        // Gets a resource given its ID
        Resource& get(Identifier id);
};

// Because we used templates, it's impossible to include ResourceHolder.hpp in
// the ResourceHolder.cpp file, so it's necessary to do it the other way around.
// Also, we change the .cpp extension to .tpp because Code::Blocks automatically
// compiles all files with .cpp extension, and ResourceHolder.tpp should not
// be compiled individually

#include "ResourceHolder.tpp"

#endif // __TEXTURE_HOLDER__
