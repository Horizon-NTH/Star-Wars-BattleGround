#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Object.h"
#include "Character.h"
#include "Weapon.h"

class Inventory
{
	friend class Player;
	friend class MainPlayer;
	friend class Planet;
	friend class Game;

public:
	Inventory();
	~Inventory();

protected:
	Character* m_character_array[5];
	std::vector<Object*> m_object_array;
	int m_level, m_objectNumber, m_characterNumber;

	int get_weapon_durability_needed();
	void repare_weapon();
	void add_character(Character* character, bool bot = true);
	void add_object(Object* object, bool bot = true);
	void add_weapon(Weapon* weapon);
	void delete_character(Character* character);
	void delete_object(Object* object);
	bool is_character_in(Character* character) const;
	bool is_object_in(Object* object) const;
	void upgrade(int numberLevelAdd, bool bot = true);
	void stat(std::ostream& os) const;

	friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory);
};

