#include "ResourceManager.h"

ResourceManager ResourceManager::s_instance;

bool ResourceManager::LoadTexture(TextureID id, const std::string& filename)
{
    sf::Texture newTexture;

    if (newTexture.loadFromFile(filename))
    {
        m_textures.insert(std::pair<TextureID, sf::Texture>(id, newTexture));
        return true;
    }

    return false;
}

sf::Texture& ResourceManager::GetTexture(TextureID id)
{
    return m_textures.at(id);
}

bool ResourceManager::LoadFont(FontID id, const std::string& filename)
{
    sf::Font newFont;

    if (newFont.loadFromFile(filename))
    {
        m_fonts.insert(std::pair<FontID, sf::Font>(id, newFont));
        return true;
    }

    return false;
}

sf::Font& ResourceManager::GetFont(FontID id)
{
    return m_fonts.at(id);
}
