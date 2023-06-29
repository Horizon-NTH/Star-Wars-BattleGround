#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

class Weapon;

class Character
{
	friend class Jedi;
	friend class Sith;
	friend class BountyHunter;
	friend class Armor;
	friend class Amplifier;
	friend class Planet;
	friend class Inventory;
	friend class Player;
	friend class MainPlayer;
	friend class Game;

public:
	Character(int level = 1, const std::string name = "", Weapon* weapon = nullptr, char type = '\0');
	~Character();

	int get_health() const;
	std::string get_name() const;
	int get_speed() const;
	int get_level() const;
	int get_xp() const;
	int get_defense() const;
	int get_attackBoost() const;
	virtual std::string get_attack_1(bool name = false) const = 0;
	virtual std::string get_attack_2(bool name = false) const = 0;

protected:
	std::string m_name;
	Weapon* m_weapon;
	int m_health, m_speed,
		m_maxHealth, m_level,
		m_xp, m_neededXP,
		m_defense, m_attackBoost,
		m_capacityLevel;

	void heal(int hp_restored);
	void set_maxHealth();
	virtual void set_maxMana() = 0;
	void take_damage(int damage_taken);
	void reinforcement(int defense_add);
	void boost_attack(int attack_add);
	bool is_alive() const;
	void add_xp(int xp);
	Weapon* set_weapon(Weapon* weapon);
	void level_up();
	void upload_level(int level, char type = '\0');
	virtual void stat(std::ostream& os) const = 0;
	void attack_basic(Character* ennemy_target, bool bot = false);
	std::string get_weapon_type() const;
	virtual void attack_1(Character* ally_target, Character* ennemy_target) = 0;
	virtual void attack_2(Character* ally_target, Character* ennemy_target) = 0;
	virtual bool is_enough_mana(int attack) const = 0;
	virtual void stat_up() = 0;
	virtual char get_type_save() const = 0;

	friend void fight(Character* ally_character, Character* enemy_character);
	friend std::ostream& operator<<(std::ostream& os, const Character& character);
};

