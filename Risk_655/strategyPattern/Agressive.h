

#include "Strategy.h"

using namespace std;

class Agressive : public Strategy
{
public:
    Agressive();
	string getType() {
		return "Agressive";
	}
    ~Agressive();
    bool decideAttack(Player* p, Map * map);
};