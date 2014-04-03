/*
 * MenuState.h
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "GameState.h"
#include "GameStateManager.h"

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Player.h"

class MenuState: public GameState
{
public:
	MenuState(RenderWindow& window, GameStateManager* manager);
	virtual ~MenuState();

	virtual bool update();
	virtual void draw(RenderWindow& window);

	virtual void EnterState();
	virtual void LeaveState();

private:
	bool m_KeyPressed[2];
	int m_Selection;
	Text m_Text[3];
	RenderWindow* m_Window;

	Ball m_Ball;
	Player m_AI1, m_AI2;
	Vector2f m_BallPos, m_BallVel;

	bool checkCollision(FloatRect r1, FloatRect r2);
	void DemoMode();
};

#endif /* MENUSTATE_H_ */
