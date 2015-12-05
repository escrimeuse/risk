#ifndef EXISTINGGAMEBUILDER_H
#define EXISTINGGAMEBUILDER_H

#include "Game.h"
#include "GameBuilder.h"
#include "../SaveLoad/SaverLoader.h"



class ExistingGameBuilder : public GameBuilder {

private:
	SaverLoader* saveload;

public:
	ExistingGameBuilder(SaverLoader* gameFile);
	void buildMap();
	void buildPlayers();
	void buildState();

	

};


#endif