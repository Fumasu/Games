/*
 * GameStateManager.cpp
 *
 *  Created on: 29.03.2014
 *      Author: Fumasu
 */

#include "GameStateManager.h"

GameState* GameStateManager::m_State =NULL;
map<string, GameState*> GameStateManager::m_States;
