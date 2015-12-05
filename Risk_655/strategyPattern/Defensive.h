#include "Strategy.h"

class Map;

using namespace std;

class Defensive : public Strategy
{
public:
    Defensive();
    ~Defensive();
	string getType() {
		return "Defensive";
	}
    bool decideAttack(Player* p, Map *map);
};