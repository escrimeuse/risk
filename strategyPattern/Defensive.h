#include "Strategy.h"

class Map;

using namespace std;

class Defensive : public Strategy
{
public:
    Defensive();
    ~Defensive();
    
    int makeAttack();
    bool decideAttack(Player* p, Map *map);
};