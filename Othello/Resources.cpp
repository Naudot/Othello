#include "Resources.h"

Resources::Resources()
{
}

Resources::~Resources()
{
	deleteTextures();
}

bool Resources::load()
{
	if (!loadTexture("field")) return false;
	if (!loadTexture("white")) return false;
	if (!loadTexture("black")) return false;
	if (!m_font.loadFromFile("data/font.otf"))
		return false;
	return true;
}

sf::Texture const &Resources::getTexture(std::string key) const
{
	std::map<std::string, sf::Texture *>::const_iterator it;
	it = m_textures.find(key);
	if (it == m_textures.end())
		throw std::runtime_error("Cannot retrieve texture " + key);
	return *it->second;
}

sf::Font const &Resources::getFont() const
{
	return m_font;
}

bool Resources::loadTexture(std::string key)
{
	sf::Texture *texture(new sf::Texture());
	std::string filename("data/" + key + ".png");

	if (!texture->loadFromFile(filename))
	{
		delete texture;
		return false;
	}

	m_textures[key] = texture;
	return true;
}

void Resources::deleteTextures()
{
	std::map<std::string, sf::Texture *>::iterator it;

	for (it = m_textures.begin(); it != m_textures.end(); ++it)
		delete it->second;
}