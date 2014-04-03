/*
 * InputComponent.h
 *
 *  Created on: 24.03.2014
 *      Author: Fumasu
 */

#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

#include "Player.h"

class Player;

////////////////////////////////////////////////////////////
/// \brief Interface Klasse für die einzelnen Eingabearten
/// des Spiels
////////////////////////////////////////////////////////////
class InputComponent
{
public:
	InputComponent(){ }
	virtual ~InputComponent(){ }

	////////////////////////////////////////////////////////////
	/// \brief virtuelle Methode zum einlesen der Spieler Eingabe und verändern des Player Objekts
	///
	/// \param player das Player Objekt, dass verändert werden soll
	/// \param deltaTime die vergangene Zeit, seit dem letzten Frame (wird benutzt für Frame Independant Movement)
	////////////////////////////////////////////////////////////
	virtual void update(Player& player, sf::Time deltaTime){ }
private:
};

#endif /* INPUTCOMPONENT_H_ */
