#include <SFML/Graphics.hpp>

#ifndef HUDTEXT_H
#define	HUDTEXT_H

class HUDText {
private:
	sf::Text text;
	sf::Vector2f position;
	sf::FloatRect bounds;

public:
	HUDText(const std::string& content, const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position, bool setCenter);

	void setContent(const std::string& content);

	sf::Text getText();

	bool isMouseOver();

	void update();

	bool isMouseClicked(const sf::Event& event);

	bool handleEvent(const sf::Event& event);

};

#endif 
