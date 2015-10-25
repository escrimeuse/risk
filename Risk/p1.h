class Player {

private:

	// data members
	string name; 					// player's name
	Country* ownedCountries;		// collection of counties owned by the player
	int numOfOwnedCountries;		// number of countries owned by player


public:

	// Constructors
	Player();
	Player(string aName);
	Player(string aName, Country* countries, int num);

	// Mutators
	void setOwnedCountries(Country* countries);
	void setName(string aName);

	// Accessors
	string getName();
	Country* getOwnedCountries();



}

#endif

