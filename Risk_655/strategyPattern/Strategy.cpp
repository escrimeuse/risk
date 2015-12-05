#include "Strategy.h"
#include "../Player/Player.h"

using namespace std;

Strategy::Strategy(){
	attackingCountry = NULL;
	defendingCountry = NULL;
}

Country* Strategy::getAttackingCountry(){
    return attackingCountry;
}
Country* Strategy::getDefendingCountry(){
    return defendingCountry;
}

void Strategy::setAttackingCountry(Country* c){
    attackingCountry = c;
}
void Strategy::setDefendingCountry(Country* c){
    defendingCountry = c;
}