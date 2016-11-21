#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Resources
{
public:
	Resources();
	~Resources();
	
	bool load();
	sf::Texture const &getTexture(std::string key) const;
	sf::Font const &getFont() const;

private:
	bool loadTexture(std::string key);
	void deleteTextures();

	std::map<std::string, sf::Texture *> m_textures;
	sf::Font m_font;
};