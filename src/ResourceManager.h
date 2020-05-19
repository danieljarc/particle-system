#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

enum class TextureID
{
    Icon
};

enum class FontID
{
    Main
};

class ResourceManager
{
public:
    static ResourceManager& GetInstance() { return s_instance; };
    ResourceManager(const ResourceManager&) = delete;

    bool LoadTexture(TextureID id, const std::string& filename);
    sf::Texture& GetTexture(TextureID id);

    bool LoadFont(FontID id, const std::string& filename);
    sf::Font& GetFont(FontID id);

private:
    ResourceManager() {}
    static ResourceManager s_instance;
    std::map<TextureID, sf::Texture> m_textures;
    std::map<FontID, sf::Font> m_fonts;
};
