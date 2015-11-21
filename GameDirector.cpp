#include "GameDirector.h"
#include "GameBuilder.h"

GameDirector::GameDirector(GameBuilder* game) {
	theGame = game;
}

void GameDirector::constructGame() {
	theGame->buildMap();
	theGame->buildPlayers();
	theGame->buildState();
}

Game* GameDirector::returnGame() {
	return theGame->getGame();
}