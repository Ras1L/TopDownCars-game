#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include "global.h"

#include <memory>
#include <unordered_map>

// Class of acquiring, accessing and releasing resources
template <class Resource, class Identifier>
class ResourceHolder
{
public:
    using resource_type = Resource;
    using id_type = Identifier;

public:
    void load(id_type, const std::string&);

    // Overload loadFromFile(), that takes extra parameter
    template<class Param>
    void load(id_type, const std::string&, const Param&);

    sf::Texture&       get(id_type);
    const sf::Texture& get(id_type) const;

private:
    std::unordered_map
    <id_type, std::unique_ptr<resource_type>>
    mResourceMap;
};

// type definition
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#include "resource_holder.inl"

#endif