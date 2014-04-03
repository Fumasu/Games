/*
 * MenuState.cpp
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#include "MenuState.h"

#include "Game.h"
#include "PlayState.h"
#include "OptionsMenu.h"

//DemoMode
#include "AIInput.h"
#include "Player.h"

//TODO: Auto Spielen

MenuState::MenuState(RenderWindow& window, GameStateManager* manager) : GameState(manager), m_KeyPressed(), m_Selection(0), m_Window(&window),
m_AI1(Vector2f(8 + Player::PlayerSize.x / 2, window.getSize().y / 2), new AIInput(m_Ball)), m_AI2(Vector2f(window.getSize().x - 8 - Player::PlayerSize.x / 2, window.getSize().y / 2), new AIInput(m_Ball)), m_Ball(Vector2f(window.getSize().x / 2, window.getSize().y / 2)){
	m_Text[0].setString("Start Game/Resume");
	m_Text[1].setString("Options");
	m_Text[2].setString("Quit");

	if(Game::m_Font ==NULL) {
		throw string("The Font was not loaded");
	}
	m_Text[0].setFont(*Game::m_Font);
	m_Text[1].setFont(*Game::m_Font);
	m_Text[2].setFont(*Game::m_Font);

	m_Text[0].setColor(Color::Yellow);
	m_Text[1].setColor(Color::White);
	m_Text[2].setColor(Color::White);

	int x;
	int y;

	x =(window.getSize().x - m_Text[0].getLocalBounds().width) * 0.5f;
	y =window.getSize().y * 0.5f - m_Text[0].getLocalBounds().height * 2;
	m_Text[0].setPosition(x, y);

	x =(window.getSize().x - m_Text[1].getLocalBounds().width) * 0.5f;
	y =window.getSize().y * 0.5f;
	m_Text[1].setPosition(x, y);

	x =(window.getSize().x - m_Text[2].getLocalBounds().width) * 0.5f;
	y =window.getSize().y * 0.5f + m_Text[2].getLocalBounds().height * 2;
	m_Text[2].setPosition(x, y);

	//DemoMode
	m_Ball.kickBall(346.41016151377545870548926830117f, 200.f);
	m_AI1.setBounds(window.getSize());
	m_AI2.setBounds(window.getSize());

	m_BallPos =m_Ball.getPosition();
	m_BallVel =m_Ball.getVelocity();
}

MenuState::~MenuState() {
}

bool MenuState::update() {
	m_Text[m_Selection].setColor(Color::White);

	if(Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		if(!m_KeyPressed[0]) {
			m_KeyPressed[0] =true;
			m_Selection--;
		}
	}
	else {
		m_KeyPressed[0] =false;
	}

	if(Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		if(!m_KeyPressed[1]) {
			m_KeyPressed[1] =true;
			m_Selection++;
		}
	}
	else {
		m_KeyPressed[1] =false;
	}

	if(m_Selection <0) m_Selection =2;
	if(m_Selection >2) m_Selection =0;

	m_Text[m_Selection].setColor(Color::Yellow);

	if(Keyboard::isKeyPressed(Keyboard::Key::Return)) {
		switch(m_Selection) {
			case 0:
				if(m_Manager->getStateByName("Play") ==NULL) m_Manager->createState("Play", new PlayState(*m_Window, m_Manager));
				m_Manager->changeState(m_Manager->getStateByName("Play"));
				break;	//Start Game
			case 1:
				if(m_Manager->getStateByName("Options") ==NULL) m_Manager->createState("Options", new OptionsMenu(*m_Window, m_Manager));
				m_Manager->changeState(m_Manager->getStateByName("Options"));
				break;	//Options
			case 2:
				return false;
		}
	}

	return true;
}

void MenuState::draw(RenderWindow& window) {
	//Demo Mode
	DemoMode();
	//Demo Mode

	window.draw(m_Text[0]);
	window.draw(m_Text[1]);
	window.draw(m_Text[2]);
}

void MenuState::EnterState() {
	m_Ball.update(false);
	Game::Gamevolume =0.f;

	m_Ball.setPosition(m_BallPos);
	m_Ball.setVelocity(m_BallVel);
}

void MenuState::LeaveState() {
	Game::Gamevolume =100.f;
	m_BallPos =m_Ball.getPosition();
	m_BallVel =m_Ball.getVelocity();
}

bool MenuState::checkCollision(FloatRect r1, FloatRect r2) {
	return (r1.left <=r2.left + r2.width &&
	   r2.left <=r1.left + r1.width &&
	   r1.top <=r2.top + r2.height &&
	   r2.top <=r1.top + r1.height);
}

void MenuState::DemoMode() {
	if(checkCollision(m_Ball.getBounds(), m_AI1.getBounds()) || checkCollision(m_Ball.getBounds(), m_AI2.getBounds())) {
		Vector2f vel;

		vel =m_Ball.getVelocity();

		vel.x *=-1.f;
		m_Ball.setVelocity(vel);
	}

	m_AI1.update();
	m_AI2.update();
	m_Ball.update(true);

	m_AI1.draw(*m_Window);
	m_AI2.draw(*m_Window);
	m_Ball.draw(*m_Window);
}
