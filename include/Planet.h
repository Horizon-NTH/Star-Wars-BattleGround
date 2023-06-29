#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include "NPC.h"
#include "Object.h"
#include "Amplifier.h"
#include "Armor.h"
#include "Weapon.h"
#include "Character.h"
#include "MainPlayer.h"
#include "Jedi.h"
#include "Sith.h"
#include "BountyHunter.h"
#include "Game.h"

#define PLANET_NUMBER 4

class Planet
{
	friend class Game;

public:
	Planet(std::string name, std::string boss_namen, int difficulty, int numberCharacterMax);
	~Planet();
	std::string get_name() const;
	bool open() const;

private:
	std::string m_name;
	NPC* m_boss;
	Character* m_training_character;
	bool m_open;
	int m_numberObject, m_numberCharacter, m_numberCharacterMax, m_difficulty;

	void add_jedi_boss(std::string name, int level,
		std::string weapon_name, int weapon_damage, int weapon_durability, char type = 'j');
	void add_sith_boss(std::string name, int level,
		std::string weapon_name, int weapon_damage, int weapon_durability, char type = 's');
	void add_bounty_hunter_boss(std::string name, int level,
		std::string weapon_name, int weapon_damage, int weapon_durability, char type = 'b');
	void add_amplifier_boss(std::string name, int level, amplifier_type type);
	void add_armor_boss(std::string name, int level);
	void stat(std::ostream& os) const;
	void shop(Game* game, MainPlayer* player);
	bool enough_money(MainPlayer* player, int money) const;
	void set_open();
	void explore(Game* game, MainPlayer* player);
	void random_fight(Game* game, MainPlayer* player);
	void boss_fight(Game* game, MainPlayer* player);

	friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
};