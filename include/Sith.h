#pragma once

#include "ForceUser.h"

#define NAME_SITH_NUMBER 20

class Sith : public ForceUser
{
	friend class Planet;

public:
	Sith(int level = 1, const std::string name = "", Weapon* weapon = nullptr, char type = '\0');
	~Sith();

	std::string get_attack_1(bool name = false) const;
	std::string get_attack_2(bool name = false) const;

protected:
	std::vector<std::string> m_nameList;

	void get_name();
	void set_name();
	void attack_1(Character* ally_target, Character* ennemy_target);
	void attack_2(Character* ally_target, Character* ennemy_target);
	bool is_enough_mana(int attack) const;
	void stat_up();
	void stat(std::ostream& os) const;
	char get_type_save() const;
};

