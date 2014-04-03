/*
 * AIInput.h
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#ifndef AIINPUT_H_
#define AIINPUT_H_

#include "InputComponent.h"

#include "Ball.h"

//////////////////////////////
/// \brief Eingabe Klasse für den KI Spieler
//////////////////////////////
class AIInput : public InputComponent {
public:
	//////////////////////////////
	/// \brief
	///
	/// \param ball Referenz auf das Ball Objekt
	//////////////////////////////
	AIInput(Ball& ball) : m_Ball(&ball) { }

	AIInput() : m_Ball(NULL) { }

	virtual ~AIInput(){ }

	virtual void update(Player& player, sf::Time deltaTime);

private:
	Ball* m_Ball;
};

#endif /* AIINPUT_H_ */
