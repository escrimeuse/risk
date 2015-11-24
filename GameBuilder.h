#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H


#include "Game.h"

class GameBuilder {

protected:
	Game* myGame;

public:
	virtual void buildMap() = 0;
	virtual void buildPlayers() = 0;
	virtual void buildState() = 0; 
	Game* getGame() {
		return myGame;
	}
	
};

#endif