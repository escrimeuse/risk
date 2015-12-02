

#include "Agressive.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

using namespace std;

Agressive::Agressive() : Strategy(){}

bool Agressive::decideAttack(Player* p, Map* map){
    list<Country*>  *playersCountries = p->getOwnedCountries();
	for (list<Country*>::iterator i = playersCountries->begin(); i != playersCountries->end(); ++i) {
        cout << (*i)->getName() << endl;
        if ((*i)->getArmies() >= 2) {
            vector<Country*> enemies = map->getEnemyCountries((*i));
            cout << "\n\n";
            for (int j = 0; j != enemies.size(); j++)
                cout << enemies[j]->getName() << endl;
            for (int j = 0; j != enemies.size(); j++) {
                if((*i)->getOwner()->getName() != enemies[j]->getOwner()->getName()){
                    if((*i)->getArmies() > enemies[j]->getArmies()){
                        setAttackingCountry((*i));
                        setDefendingCountry(enemies[j]);
                        return true;
                    }
                }
            }
        }
    }
	return false;
}