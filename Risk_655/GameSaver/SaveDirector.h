#ifndef SAVEDIRECTOR_H
#define SAVEDIRECTOR_H

#include "SaveGameBuilder.h"

class SaveDirector {

private:
	SaveGameBuilder* theSaver;

public: 
	SaveDirector(SaveGameBuilder* saver);
	void saveGame();


};
#endif
