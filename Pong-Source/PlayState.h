/*
 * PlayState.h
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "GameState.h"
#include "Player.h"
#include "Ball.h"

#include "GameStateManager.h"

using namespace sf;

class PlayState : public GameState
{
public:
	PlayState(RenderWindow& window, GameStateManager* manager);
	virtual ~PlayState();

	virtual bool update();
	virtual void draw(RenderWindow& window);

	virtual void EnterState();
	virtual void LeaveState();

private:
	Player m_PlayerPaddle, m_AIPaddle;
	Ball m_Ball;
	Clock m_Clock;
	RenderWindow* m_Window;
	bool m_Playing;
	Sound m_Sound;
	SoundBuffer m_BallHit;
	int m_Points[2];

	bool m_isRotating;
	float m_Angle;
	bool m_RotateUp;

	bool checkCollision(const FloatRect r1, const FloatRect r2);
};

#endif /* PLAYSTATE_H_ */
