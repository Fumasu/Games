/*
 * GameStateManager.h
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include <SFML/Graphics.hpp>

#include "GameState.h"

#include <map>
#include <string>

using namespace std;

class GameStateManager
{
public:
	~GameStateManager() {
		if(m_State) {
			delete m_State;
			m_State =NULL;
		}
	}

	static GameState* getActiveState() { return m_State; }

	static void changeState(GameState* newState) {
		if(m_State) {
			m_State->LeaveState();
		}

		m_State =newState;
		m_State->EnterState();
	}

	static bool update() {
		return m_State->update();
	}

	static void draw(sf::RenderWindow& window) {
		m_State->draw(window);
	}

	static GameState* getStateByName(const string state) {
		map<string, GameState*>::iterator it;

		it =m_States.find(state);
		if(it !=m_States.end()) return it->second;

		return NULL;
	}

	static void createState(const string stateName, GameState* state) {
		m_States[stateName] =state;
	}

private:
	static GameState* m_State;
	static map<string, GameState*> m_States;
};

#endif /* GAMESTATEMANAGER_H_ */
