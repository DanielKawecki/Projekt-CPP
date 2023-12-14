#include <SFML/Graphics.hpp>
#include "hudText.h"

HUDText::HUDText(const std::string& content, const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position, bool setCenter)
	: text(content, font, characterSize), position(position) {
	text.setFillColor(color);
	text.setPosition(position);

	if (setCenter)
		text.setOrigin((int)(text.getLocalBounds().width / 2.f), (int)(text.getLocalBounds().height/ 2.f));
}

void HUDText::setContent(const std::string& content) {
	text.setString(content);
}

sf::Text HUDText::getText() {
	return text;
}