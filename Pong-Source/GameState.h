/*
 * GameState.h
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class GameStateManager;

////////////////////////////////////////////////////////////
/// \brief Interface Klasse für die im Spiel genutzten Spiel-Zustände
///
////////////////////////////////////////////////////////////
class GameState
{
public:
	GameState(GameStateManager* manager) {
		m_Manager =manager;
	}
	virtual ~GameState(){ }

	////////////////////////////////////////////////////////////
	/// \brief virtuelle Methode zum Aktualisieren des GameState
	///
	/// \return Liefert \b false, falls das Spiel beendet werden soll, sonst \b true
	////////////////////////////////////////////////////////////
	virtual bool update(){ return true; }

	////////////////////////////////////////////////////////////
	/// \brief virtuelle Methode zum Zeichnen des GameState
	////////////////////////////////////////////////////////////
	virtual void draw(RenderWindow& window){ }

	////////////////////////////////////////////////////////////
	/// \brief virtuelle Methode, die beim Betreten des GameState ausgeführt wird
	////////////////////////////////////////////////////////////
	virtual void EnterState(){ }

	////////////////////////////////////////////////////////////
	/// \brief virtuelle Methode, die beim Verlassen des GameState ausgeführt wird
	///
	/// Hier werden die nötigen Schritte unternommen, bspw. das Spiel in Pause versetzt
	/// oder die Musik gestoppt
	////////////////////////////////////////////////////////////
	virtual void LeaveState(){ }

protected:
	GameStateManager* m_Manager;
};

#endif /* GAMESTATE_H_ */
