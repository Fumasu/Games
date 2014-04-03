/*
 * Ball.h
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#ifndef BALL_H_
#define BALL_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

////////////////////////////////////////////////////////////
/// \brief Klasse für den Ball
///
////////////////////////////////////////////////////////////
class Ball
{
public:
	//////////////////////////////
	/// \param position Die Position des Balls
	//////////////////////////////
	Ball(Vector2f position);

	//////////////////////////////
	/// \param window das RenderWindow, auf das gezeichnet werden soll
	//////////////////////////////
	void draw(RenderWindow& window);

	//////////////////////////////
	/// \brief Updates the Position
	///
	/// \param playing \b false wenn das Spiel pausiert ist, sonst \b true
	//////////////////////////////
	void update(bool playing);

	//////////////////////////////
	/// \brief
	//////////////////////////////
	bool isMoving() const {
		if(m_Velocity.x ==0 && m_Velocity.y ==0) return false;

		return true;
	}

	//////////////////////////////
	/// \brief
	//////////////////////////////
	void kickBall(const int x_vel, const int y_vel) {
		m_Velocity.x =x_vel;
		m_Velocity.y =y_vel;
	}

	//////////////////////////////
	/// \brief
	//////////////////////////////
	Vector2f getVelocity() const {
		return m_Velocity;
	}

	//////////////////////////////
	/// \brief
	//////////////////////////////
	void setVelocity(const Vector2f vel) {
		m_Velocity =vel;
	}

	void setPosition(const Vector2f position);
	Vector2f getPosition() const { return m_Position; }
	FloatRect getBounds() const;

private:
	Vector2f m_Position;
	CircleShape m_Shape;
	Clock m_Clock;
	Vector2f m_Velocity;
	Sound m_Sound;
	SoundBuffer m_BallHit;

	////////////////////////////////////////////////////////////
	// Static member data
	////////////////////////////////////////////////////////////
	static constexpr float BallRadius{10.f};
	static constexpr float BallSpeed{50.f};
};

#endif /* BALL_H_ */
