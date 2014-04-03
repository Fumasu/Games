/*
 * Player.h
 *
 *  Created on: 24.03.2014
 *      Author: Fumasu
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "InputComponent.h"

using namespace sf;

class InputComponent;

class Player
{
public:
	friend class PlayerInput;

	Player(Vector2f position, InputComponent* input);

	void draw(RenderWindow& window);
	void update();

	Vector2f getPosition() const { return m_Position; }
	void setPosition(const Vector2f position);

	/////////////////////////////////////
	/// \brief Setzt die Grenze, in der sich das Paddle bewegen kann
	///
	/// \param bounds Grenze für die Paddle-Bewegung
	/////////////////////////////////////
	void setBounds(const Vector2u bounds);

	/////////////////////////////////////
	/// \brief Gibt die Position und Grösse des Paddles zurück
	///
	/// \return die Grösse und Position des Paddles
	/////////////////////////////////////
	FloatRect getBounds() const;

	static const Vector2f PlayerSize;
	static constexpr float PlayerSpeed =200.f;

protected:
	Vector2f m_Position;
	Vector2u m_Bounds;

private:
	InputComponent* m_Input;
	RectangleShape m_Shape;
	Clock m_Clock;
};

#endif /* PLAYER_H_ */
