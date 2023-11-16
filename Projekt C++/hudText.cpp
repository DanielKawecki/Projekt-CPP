#include <SFML/Graphics.hpp>
#include "hudText.h"

HUDText::HUDText(const std::string& content, const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position)
	: text(content, font, characterSize), position(position) {
	text.setFillColor(color);
	text.setPosition(position);
}

void HUDText::setContent(const std::string& content) {
	text.setString(content);
}

sf::Text HUDText::getText() {
	return text;
}