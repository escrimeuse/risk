#ifndef GAMEDIRECTOR_H
#define GAMEDIRECTOR_H

#include "GameBuilder.h"

class GameDirector {

private:
	GameBuilder* theGame; 

public:
	GameDirector(GameBuilder* game);
	void constructGame();
	Game* returnGame();
};

#endif