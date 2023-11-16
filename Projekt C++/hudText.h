#include <SFML/Graphics.hpp>

#ifndef HUDTEXT_H
#define	HUDTEXT_H

class HUDText {
private:
	sf::Text text;
	sf::Vector2f position;

public:
	HUDText(const std::string& content, const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position);

	void setContent(const std::string& content);

	sf::Text getText();
};

#endif 
