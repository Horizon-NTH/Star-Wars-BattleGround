#pragma once

#include "Character.h"
#include "Weapon.h"

#define NAME_BOUNTYHUNTER_NUMBER 186

class BountyHunter :
	public Character
{
	friend class Planet;

public:
	BountyHunter(int level = 1, const std::string name = "", Weapon* weapon = nullptr, char type = '\0');
	~BountyHunter();
	std::string get_attack_1(bool name = false) const;
	std::string get_attack_2(bool name = false) const;

protected:
	std::vector<std::string> m_nameList;

	void get_name();
	void set_name();
	void set_maxMana();
	void attack_1(Character* ally_target, Character* ennemy_target);
	void attack_2(Character* ally_target, Character* ennemy_target);
	bool is_enough_mana(int attack) const;
	void stat_up();
	void stat(std::ostream& os) const;
	char get_type_save() const;
};

