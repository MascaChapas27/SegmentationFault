#include <assert.h>

template <class Resource, class Identifier>
void ResourceHolder<Resource,Identifier>::load(Identifier id, const std::string& fileName){
    // Unique pointers are better because they delete themselves when
    // they go out of scope
    std::unique_ptr<Resource> resource(new Resource());

    // We try to load the resource. If there is an error, we throw an exception
    if(!resource->loadFromFile(fileName))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);

    // It's important to std::move the pointer so that it's not destroyed
    // as soon as the function ends. Also, the insert function returns a pair
    // of elements. The second one is a boolean, which is true if everything went OK
    auto inserted = resourceMap.insert(std::make_pair(id,std::move(resource)));

    // The insertion MUST be valid. If it's not, I screwed up while writing code and
    // loaded the same thing twice. Also, I know writing assert(insert.second) would have
    // the same effect, but I want the code to be very readable and obvious
    assert(inserted.second == true);
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource,Identifier>::get(Identifier id){
    // First we find the element in the map (auto means that the
    // type is automatically infered from the context)
    auto found = resourceMap.find(id);

    // If the element is not found, then the variable found contains
    // a special value that is associated with the "end" of the map
    assert(found != resourceMap.end());

    // Once we have the element, which is a pair, we return
    // the texture, which is the second element
    return *found -> second;
}
