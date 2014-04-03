/*
 * PlayerInput.h
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#ifndef PLAYERINPUT_H_
#define PLAYERINPUT_H_

#include "InputComponent.h"

class PlayerInput : public InputComponent
{
public:
	PlayerInput();
	virtual ~PlayerInput(){ };

	virtual void update(Player& player, Time deltaTime);

private:
};

#endif /* PLAYERINPUT_H_ */
