#ifndef SAVEGAMEBUILDER_H
#define SAVEGAMEBUILDER_H


class SaveGameBuilder {


public:
	virtual void saveMap() = 0;
	virtual void savePlayers() = 0;
	virtual void saveState() = 0;

};
#endif
