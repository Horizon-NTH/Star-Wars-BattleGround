#pragma once

#include <iostream>
#include <string>

#include "Inventory.h"

class Player
{
	friend class Planet;

public:
	Player(std::string name);
	~Player();
	std::string get_name() const;

protected:
	std::string m_name;
	Inventory* m_inventory;
	virtual void stat(std::ostream& os) const = 0;
	void boost();
	void unboost();
	bool add_character_alive() const;

	friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

