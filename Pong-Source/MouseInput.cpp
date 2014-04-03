/*
 * MouseInput.cpp
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#include "MouseInput.h"

void MouseInput::update(Player& player, Time deltaTime) {
	Vector2f worldPos(Mouse::getPosition(*m_Window).x, Mouse::getPosition(*m_Window).y);
	Vector2f targetPos;

	targetPos.x =player.getPosition().x;
	targetPos.y =m_Window->mapCoordsToPixel(worldPos).y;

	player.setPosition(targetPos);
}
