/*
 * Application.h
 *
 *  Created on: 23.03.2014
 *      Author: Fumasu
 */

#ifndef GAME_H_
#define GAME_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <string>

#include "GameStateManager.h"
#include "PlayState.h"
#include "MenuState.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////
/// \brief Die Haupt-Klasse für die Anwendung
///
////////////////////////////////////////////////////////////
class Game
{
public:
	Game();
	~Game();

	////////////////////////////////////////////////////////////
	/// \brief Startet das Spiel
	///
	/// \param argc Die Anzahl der Command-Line Argumente
	/// \param argv Die Command-Line Argumente
	///
	////////////////////////////////////////////////////////////
	int Run(int argc, char *argv[]);

	static Font *m_Font;
	static FloatRect m_WindowSize;
	static float Gamevolume;

private:
	static constexpr int WindowWidth{1024}, WindowHeight{768};
	static constexpr float PaddleSpeed{5.f};
	const string WindowTitle{"Pong"};

	RenderWindow m_Window;
	Text m_Text;
	bool m_Done;
	GameStateManager m_StateManager;

	void handleEvent(Event &event);
	void drawScene();
	void handleInput();
	void updateGame();
};

#endif /* GAME_H_ */
