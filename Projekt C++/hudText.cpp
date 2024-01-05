#include <SFML/Graphics.hpp>
#include <iostream>
#include "hudText.h"

HUDText::HUDText(const std::string& content, const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position, bool setCenter)
	: text(content, font, characterSize), position(position) {
	text.setFillColor(color);
	text.setPosition(position);

	if (setCenter)
		text.setOrigin((int)(text.getLocalBounds().width / 2.f), (int)(text.getLocalBounds().height/ 2.f));

	bounds = text.getGlobalBounds();
	//bounds.left = position.x;
	//bounds.top = position.y;
	
}

void HUDText::setContent(const std::string& content) {
	text.setString(content);
}

sf::Text HUDText::getText() {
	return text;
}

bool HUDText::isMouseOver() {
	float mouse_x = sf::Mouse::getPosition().x;
	float mouse_y = sf::Mouse::getPosition().y;
	//std::cout << bounds.top << " " << bounds.left << std::endl;
	return bounds.contains(mouse_x, mouse_y);
}

void HUDText::update() {
	if (isMouseOver()) {
		text.setFillColor(sf::Color::Green);
	}
	else {
		text.setFillColor(sf::Color::White);
	}
}

bool HUDText::isMouseClicked(const sf::Event& event) {
	return event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
}

bool HUDText::handleEvent(const sf::Event& event) {
	if (isMouseOver()) {
		if (isMouseClicked(event)) {
			return true;
		}
	}
	return false;
}
