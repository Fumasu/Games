/*
 * PlayState.cpp
 *
 *  Created on: 25.03.2014
 *      Author: Fumasu
 */

#include "PlayState.h"

#include "PlayerInput.h"
#include "AIInput.h"
#include "MenuState.h"
#include "Game.h"
#include "MouseInput.h"

#include <sstream>
#include <cmath>

#include <iostream>

PlayState::PlayState(RenderWindow& window, GameStateManager* manager) : GameState(manager), m_PlayerPaddle(Vector2f(8 + Player::PlayerSize.x / 2, window.getSize().y / 2),
		new /*PlayerInput*/MouseInput(window)), m_AIPaddle(Vector2f(window.getSize().x - 8 - Player::PlayerSize.x / 2, window.getSize().y / 2), new AIInput(m_Ball)),
		m_Ball(Vector2f(window.getSize().x / 2, window.getSize().y / 2)), m_Window(&window), m_Playing(false), m_Points{0}, m_isRotating(false), m_Angle(0.f), m_RotateUp(false) {

	m_PlayerPaddle.setBounds(window.getSize());
	m_AIPaddle.setBounds(window.getSize());
	m_BallHit.loadFromFile("res/ball_hit.wav");
	m_Sound.setBuffer(m_BallHit);
	//m_Ball.setBounds(window.getSize());
}

PlayState::~PlayState() {
}

bool PlayState::checkCollision(FloatRect r1, FloatRect r2) {
	return (r1.left <=r2.left + r2.width &&
	   r2.left <=r1.left + r1.width &&
	   r1.top <=r2.top + r2.height &&
	   r2.top <=r1.top + r1.height);
}

float fmap(float value, float au, float ao, float zu, float zo) {
	float ausgang =(::abs(au) + ::abs(ao));
	float ziel =(::abs(zu) + ::abs(zo));

	float faktor =ziel / ausgang;

	return value * faktor + zu - (au * faktor);
}

bool PlayState::update() {
	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
		m_Playing =false;

		if(m_Manager->getStateByName("Menu") ==NULL) {
			m_Manager->createState("Menu", new MenuState(*m_Window, m_Manager));
		}

		m_Manager->changeState(m_Manager->getStateByName("Menu"));

		return true;
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::Space) && !m_Playing) {
			m_Playing =true;

			//wenn Ball sich nicht bewegt (neues Spiel), dann Ball "anstosen"
			if(!m_Ball.isMoving()) {
				m_Ball.kickBall(-400, 0);  //BallSpeed
			}
	}
	/*else if(Keyboard::isKeyPressed(Keyboard::Key::Z)) {
		m_isRotating =true;
	}*/

	View view(Game::m_WindowSize);

	view.rotate(m_Angle);
	m_Window->setView(view);

	if(m_isRotating) {
		switch(m_RotateUp) {
			case true:
				m_Angle -=5.f;

				if(m_Angle <=0.f) {
					m_isRotating =false;
					m_Angle =0.f;

					m_RotateUp =false;
				}
				break;
			case false:
				m_Angle +=5.f;

				if(m_Angle >=180.f) {
					m_isRotating =false;
					m_Angle =180.f;

					m_RotateUp =true;
				}
				break;
		}

		/*m_Ball.update(false);

		return true;*/
	}

	if(m_Playing) {
		//Collision Detection & Response
		//mit Player Paddle
		if(checkCollision(m_Ball.getBounds(), m_PlayerPaddle.getBounds())) {
			Vector2f vel =m_Ball.getVelocity();
			float ballSpeed =sqrt(vel.x * vel.x + vel.y * vel.y);

			//Abstand Mittelpunkt Paddle --> Mittelpunkt Ball
			float abstand =m_PlayerPaddle.getPosition().y - m_Ball.getPosition().y;
			float winkel =fmap(abstand, -25.f, 25.f, -45.f, 45.f);

			if(winkel >45.f) winkel =45.f;
			if(winkel <-45.f) winkel =-45.f;
			if(winkel <0) winkel =360.f + winkel;

			vel.x =cos(winkel * (3.14159f / 180.f)) * ballSpeed;
			vel.y =-sin(winkel * (3.14159f / 180.f)) * ballSpeed;
			m_Ball.setVelocity(vel);

			//Setze die Lautstärke auf die vom Game vorgegebene
			m_Sound.setVolume(Game::Gamevolume);
			m_Sound.play();
		}
		//mit AI Paddle
		if( checkCollision(m_Ball.getBounds(), m_AIPaddle.getBounds())) {
			Vector2f vel =m_Ball.getVelocity();
			float ballSpeed =sqrt(vel.x * vel.x + vel.y * vel.y);

			//Abstand Mittelpunkt Paddle --> Mittelpunkt Ball
			float abstand =m_AIPaddle.getPosition().y - m_Ball.getPosition().y;
			float winkel =fmap(abstand, -25.f, 25.f, -45.f, 45.f);

			if(winkel >45.f) winkel =45.f;
			if(winkel <-45.f) winkel =-45.f;
			if(winkel <0) winkel =360.f + winkel;

			vel.x =cos(winkel * (3.14159f / 180.f)) * -ballSpeed;
			vel.y =-sin(winkel * (3.14159f / 180.f)) * ballSpeed;
			m_Ball.setVelocity(vel);

			//Setze die Lautstärke auf die vom Game vorgegebene
			m_Sound.setVolume(Game::Gamevolume);
			m_Sound.play();
		}

		m_PlayerPaddle.update();
		m_AIPaddle.update();
	}
	m_Ball.update(m_Playing);

	if(m_Ball.getPosition().x < 0 || m_Ball.getPosition().x >Game::m_WindowSize.width) {	//Tor für links oder rechts
		m_Ball.getPosition().x <0 ? m_Points[1]++ : m_Points[0]++;

		m_Playing =false;
		m_Ball.setPosition(Vector2f(Game::m_WindowSize.width * 0.5f, Game::m_WindowSize.height * 0.5f));
		//m_Ball.kickBall(m_Ball.getPosition().x <0 ? -200 : 200, 0);
		m_Ball.setVelocity(Vector2f(0, 0));
	}

	if(m_Ball.getVelocity().x >0 && m_RotateUp ==false && m_Ball.getPosition().x >Game::m_WindowSize.width * 0.25f) { //Ball fliegt nach rechts und ist über der hälfte
		m_isRotating =true;
	}
	else if(m_Ball.getVelocity().x <0 && m_RotateUp ==true && m_Ball.getPosition().x < Game::m_WindowSize.width * 0.75f) {
		m_isRotating =true;
	}

	return true;
}

void PlayState::draw(RenderWindow& window) {
	m_PlayerPaddle.draw(window);
	m_AIPaddle.draw(window);
	m_Ball.draw(window);

	if(!m_Playing) {
		Text pauseText("Press Space to play", *Game::m_Font);
		pauseText.setColor(Color::White);
		pauseText.setPosition(window.getSize().x / 2 - pauseText.getLocalBounds().width / 2, window.getSize().y / 2 - pauseText.getLocalBounds().height / 2);

		window.draw(pauseText);
	}

	//Display Points
	{
		Text punkte;
		std::stringstream strstr;

		punkte.setFont(*Game::m_Font);
		punkte.setColor(Color::White);

		strstr <<m_Points[0];
		punkte.setString(strstr.str());
		punkte.setPosition(Game::m_WindowSize.width * 0.25f, 10);
		window.draw(punkte);

		strstr.str("");
		strstr <<m_Points[1];
		punkte.setPosition(Game::m_WindowSize.width * 0.75f, 10);
		punkte.setString(strstr.str());
		window.draw(punkte);
	}
}

void PlayState::EnterState() {
}

void PlayState::LeaveState() {
	//Reset View Rotation
	View view;

	view.reset(Game::m_WindowSize);
	m_Window->setView(view);
}
