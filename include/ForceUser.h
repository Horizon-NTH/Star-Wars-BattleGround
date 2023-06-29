#pragma once

#include "Character.h"
#include "Weapon.h"

class ForceUser : public Character
{
	friend class Jedi;
	friend class Sith;

public:
	ForceUser(int level = 1, const std::string name = "", Weapon* weapon = nullptr, char type = '\0');
	~ForceUser();

	int get_mana() const;

protected:
	int m_mana, m_maxMana;

	void restore_mana(int mana_restored);
	void set_maxMana();
	void decrease_mana(int mana_decrease);
};

