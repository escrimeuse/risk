#include "Strategy.h"

class Map;

using namespace std;

class Random : public Strategy
{
public:
    Random();
    ~Random();
	string getType() {
		return "Random";
	}

    bool decideAttack(Player* p, Map* map);
};