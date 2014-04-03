/*
 * OptionsMenu.h
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#ifndef OPTIONSMENU_H_
#define OPTIONSMENU_H_

#include "GameState.h"

#include "Game.h"

class OptionsMenu: public GameState
{
public:
	OptionsMenu(RenderWindow& window, GameStateManager* manager) : GameState(manager), m_Window(&window) {
		if(Game::m_Font ==NULL) {
			throw string("The Font was not loaded");
		}
		m_Text.setFont(*Game::m_Font);
		m_Text.setString("Nothing here yet\nPress Escape");
		m_Text.setColor(Color::White);
		m_Text.setPosition(window.getSize().x / 2 - m_Text.getLocalBounds().width / 2, window.getSize().y / 2 - m_Text.getLocalBounds().height / 2);
	}
	virtual ~OptionsMenu() { }

	virtual bool update() {
		if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			if(m_Manager->getStateByName("Menu") ==NULL) {
				m_Manager->createState("Menu", new MenuState(*m_Window, m_Manager));
			}
			m_Manager->changeState(m_Manager->getStateByName("Menu"));
		}
		return true;
	}

	virtual void draw(RenderWindow& window) {
		window.draw(m_Text);
	}

	virtual void EnterState() { }
	virtual void LeaveState() { }

private:
	Text m_Text;
	RenderWindow* m_Window;
};

#endif /* OPTIONSMENU_H_ */
