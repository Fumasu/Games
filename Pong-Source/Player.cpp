/*
 * Player.cpp
 *
 *  Created on: 24.03.2014
 *      Author: Fumasu
 */

#include "Player.h"

const Vector2f Player::PlayerSize(16.f, 60.f);

Player::Player(Vector2f position, InputComponent* input) : m_Position(position), m_Bounds(0, 0), m_Input(input), m_Shape(), m_Clock() {
	m_Shape.setOrigin(PlayerSize.x / 2, PlayerSize.y / 2);
	m_Shape.setFillColor(Color::Cyan);
	m_Shape.setSize(PlayerSize);
	m_Shape.setPosition(m_Position);

	m_Clock.restart();
}

void Player::draw(RenderWindow& window) {
	window.draw(m_Shape);

	/*{ //Hitbox
		RectangleShape shape;

		shape.setFillColor(Color::Transparent);
		shape.setOutlineColor(Color::White);
		shape.setOutlineThickness(1.f);
		shape.setOrigin(PlayerSize.x / 2, PlayerSize.y / 2);
		shape.setSize(PlayerSize);
		shape.setPosition(m_Position);

		window.draw(shape);
	}*/
}

void Player::update() {
	m_Input->update(*this, m_Clock.restart());
}

void Player::setBounds(const Vector2u bounds) {
	m_Bounds =bounds;
}

void Player::setPosition(Vector2f position) {
	if(position.y - PlayerSize.y / 2 <0) {
		position.y =PlayerSize.y / 2;
	}
	else if(position.y + PlayerSize.y / 2 > m_Bounds.y) {
		position.y =m_Bounds.y - PlayerSize.y / 2;
	}
	m_Position =position;
	m_Shape.setPosition(m_Position);
}

FloatRect Player::getBounds() const {
	FloatRect bounds;

	bounds.top =m_Position.y - PlayerSize.y / 2;
	bounds.left =m_Position.x - PlayerSize.x / 2;
	bounds.width =PlayerSize.x;
	bounds.height =PlayerSize.y;

	return bounds;
}
