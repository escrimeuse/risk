#include "Strategy.h"

class Map;

using namespace std;

class Random : public Strategy
{
public:
    Random();
    ~Random();
    

    bool decideAttack(Player* p, Map* map);
};