/*
 * AIInput.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#include "AIInput.h"

#include "Ball.h"

void AIInput::update(Player& player, sf::Time deltaTime) {
	if(m_Ball ==NULL) return;

	FloatRect ballRect, playerRect;
	Vector2f playerPosition;

	playerPosition =player.getPosition();

	ballRect =m_Ball->getBounds();
	playerRect =player.getBounds();

	if(ballRect.top + ballRect.height / 2 <playerRect.top + playerRect.height / 2 - 5) {
		//Ball ist über dem Player
		playerPosition.y -=player.PlayerSpeed * deltaTime.asSeconds();
		player.setPosition(playerPosition);
	}
	else if(ballRect.top + ballRect.height / 2 > playerRect.top + playerRect.height / 2 + 5) {
		//Ball ist unter dem Player
		playerPosition.y +=player.PlayerSpeed * deltaTime.asSeconds();
		player.setPosition(playerPosition);
	}
}
