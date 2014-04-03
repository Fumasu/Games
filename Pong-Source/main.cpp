/*
 * main.cpp
 *
 *  Created on: 23.03.2014
 *      Author: Fumasu
 */

#include "Game.h"

using namespace std;

int main(int argc, char **argv) {
	Game theApp;
	int ret;

	ret =theApp.Run(argc, argv);

	return ret;
}
