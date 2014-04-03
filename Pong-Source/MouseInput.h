/*
 * MouseInput.h
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#ifndef MOUSEINPUT_H_
#define MOUSEINPUT_H_

#include "InputComponent.h"

class MouseInput: public InputComponent
{
public:
	MouseInput(RenderWindow& window) : m_Window(&window) { }
	virtual ~MouseInput() { }

	virtual void update(Player& player, Time deltaTime);

private:
	RenderWindow* m_Window;
};

#endif /* MOUSEINPUT_H_ */
