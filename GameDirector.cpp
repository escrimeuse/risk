#include "GameDirector.h"
#include "GameBuilder.h"
#include <iostream>

using namespace std;

GameDirector::GameDirector(GameBuilder* game) {
	theGame = game;
}

void GameDirector::constructGame() {
	cout << "Building the map" << endl;
	theGame->buildMap();
	cout << "Building the players" << endl;
	theGame->buildPlayers();
	cout << "Building the state" << endl;
	theGame->buildState();
}

Game* GameDirector::returnGame() {
	return theGame->getGame();
}

