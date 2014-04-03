/*
 * Application.cpp
 *
 *  Created on: 23.03.2014
 *      Author: Fumasu
 */

#include "Game.h"
Font* Game::m_Font =NULL;
FloatRect Game::m_WindowSize;
float Game::Gamevolume =100.f;

Game::Game() : m_Window(), m_Done(false) {
}

Game::~Game() {
	m_Window.close();
}

void Game::handleEvent(Event &event) {
	switch(event.type) {
		case Event::Closed: m_Done =true;
			break;
		default: break;
	}
}

void Game::drawScene() {
	m_StateManager.draw(m_Window);

	m_Window.draw(m_Text);
}

int Game::Run(int argc, char* argv[]) {
	::srand(static_cast<int>(::time(NULL)));
	m_Window.create(VideoMode(WindowWidth, WindowHeight, 32), WindowTitle);

	m_WindowSize.top =0;
	m_WindowSize.left =0;
	m_WindowSize.width =WindowWidth;
	m_WindowSize.height =WindowHeight;

	//m_Window.setFramerateLimit(30);
	m_Window.setVerticalSyncEnabled(true);

	View view(FloatRect(0, 0, WindowWidth, WindowHeight));

	//view.rotate(45.f);
	m_Window.setView(view);

	m_Font =new Font();
	if(!m_Font->loadFromFile("res/Xolonium-Regular.otf")) {
		throw string("Konnte die Font Datei nicht laden: res/Xolonium-Regular.otf");
	}

	m_Text.setFont(*m_Font);
	m_Text.setString("Pong");
	m_Text.setPosition(WindowWidth / 2 - m_Text.getLocalBounds().width / 2, 0);

	m_StateManager.createState("Menu", new MenuState(m_Window, &m_StateManager));
	m_StateManager.changeState(m_StateManager.getStateByName("Menu"));

	while(!m_Done) {
		Event event;

		while(m_Window.pollEvent(event)) {
			handleEvent(event);
		}

		if(m_StateManager.update() ==false) m_Done =true;

		m_Window.clear(Color::Black);

		drawScene();

		m_Window.display();
	}

	return EXIT_SUCCESS;
}
