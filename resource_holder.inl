#include "resource_holder.hpp"

#include <assert.h>

template <class Resource, class Identifier>
void ResourceHolder<Resource, Identifier>
::load(Identifier id, const std::string& filepath)
{
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filepath)){
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filepath);
    }

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

// template for class ResourceHolder
template <class Resource, class Identifier>

// template for overloaded function with own template parameter
template <class Param>

void ResourceHolder<Resource, Identifier>
::load(Identifier id, const std::string& filepath, const Param& extra_param)
{
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filepath, extra_param)){
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filepath);
    }

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <class Resource, class Identifier>
sf::Texture& ResourceHolder<Resource, Identifier>
::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <class Resource, class Identifier>
const sf::Texture& ResourceHolder<Resource, Identifier>
::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}