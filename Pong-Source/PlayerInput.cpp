/*
 * PlayerInput.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#include "PlayerInput.h"

PlayerInput::PlayerInput() {
}

void PlayerInput::update(Player& player, sf::Time deltaTime) {
	Vector2f position =player.getPosition();

	if(Keyboard::isKeyPressed(Keyboard::Key::Up) && position.y >player.PlayerSize.y / 2) {
		position.y -=player.PlayerSpeed * deltaTime.asSeconds();
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Down) && position.y <player.m_Bounds.y - player.PlayerSize.y / 2) {
		position.y +=player.PlayerSpeed * deltaTime.asSeconds();
	}

	player.setPosition(position);
}
