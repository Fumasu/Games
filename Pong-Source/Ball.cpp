/*
 * Ball.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#include "Ball.h"

#include "Game.h"

Ball::Ball(Vector2f position) : m_Position(position), m_Velocity(0, 0) {
	m_Shape.setOrigin(BallRadius, BallRadius);
	m_Shape.setPosition(m_Position);
	m_Shape.setFillColor(Color::Red);
	m_Shape.setRadius(BallRadius);

	m_Clock.restart();

	m_BallHit.loadFromFile("res/ball_hit.wav");
	m_Sound.setBuffer(m_BallHit);
}

void Ball::draw(RenderWindow& window) {
	window.draw(m_Shape);

	/*{	//Hitbox
		RectangleShape shape;

		shape.setOrigin(BallRadius, BallRadius);
		shape.setSize(Vector2f(BallRadius * 2, BallRadius * 2));
		shape.setFillColor(Color::Transparent);
		shape.setOutlineColor(Color::White);
		shape.setOutlineThickness(1.f);
		shape.setPosition(m_Position);

		window.draw(shape);
	}*/
}

void Ball::update(bool playing) {
	float deltaTime;

	deltaTime =m_Clock.restart().asSeconds();

	if(!playing) return;

	m_Position.x +=m_Velocity.x * deltaTime;
	m_Position.y +=m_Velocity.y * deltaTime;

	if(getBounds().top <=Game::m_WindowSize.top || getBounds().top + getBounds().height >=Game::m_WindowSize.height) {
		m_Velocity.y *=-1.f;

		m_Sound.setVolume(Game::Gamevolume);
		m_Sound.play();
	}

	m_Shape.setPosition(m_Position);
}

FloatRect Ball::getBounds() const {
	FloatRect bounds;

	bounds.top =m_Position.y - BallRadius;
	bounds.left =m_Position.x - BallRadius;
	bounds.width =BallRadius * 2;
	bounds.height =BallRadius * 2;

	return bounds;
}

void Ball::setPosition(const Vector2f pos) {
	m_Position =pos;
	m_Shape.setPosition(pos);
}
