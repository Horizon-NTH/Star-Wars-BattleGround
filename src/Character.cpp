#include "Character.h"
#include "Weapon.h"

Character::Character(int level, const std::string name, Weapon* weapon, char type) :
	m_name(name), m_health(100), m_maxHealth(100),
	m_speed(100), m_level(1), m_xp(0),
	m_neededXP(1000), m_defense(0),
	m_weapon(weapon), m_attackBoost(0),
	m_capacityLevel(1)
{
	upload_level(level, type);
	if (m_weapon == nullptr)
	{
		m_weapon = new Weapon();
	}
}

Character::~Character()
{
	if (m_weapon != nullptr)
	{
		delete m_weapon;
	}
}

int Character::get_health() const
{
	return m_health;
}

std::string Character::get_name() const
{
	return m_name;
}

int Character::get_speed() const
{
	return m_speed;
}

int Character::get_level() const
{
	return m_level;
}

int Character::get_xp() const
{
	return m_xp;
}

int Character::get_defense() const
{
	return m_defense;
}

int Character::get_attackBoost() const
{
	return m_attackBoost;
}

void Character::heal(int hp_restored)
{
	if (hp_restored > 0)
	{
		m_health += hp_restored;
		if (m_health > m_maxHealth)
		{
			m_health = m_maxHealth;
		}
	}
}

void Character::set_maxHealth()
{
	m_health = m_maxHealth;
}

void Character::take_damage(int damage_taken)
{
	damage_taken -= m_defense;
	if (damage_taken > 0)
	{
		m_health -= damage_taken;
		if (m_health < 0)
		{
			m_health = 0;
		}
	}
}

void Character::reinforcement(int defense_add)
{
	if (defense_add > 0)
	{
		m_defense += defense_add;
	}
}

void Character::boost_attack(int attack_add)
{
	if (attack_add > 0)
	{
		m_attackBoost += attack_add;
	}
}

bool Character::is_alive() const
{
	return !(m_health == 0);
}

void Character::add_xp(int xp)
{
	if (xp > 0)
	{
		m_xp += xp;
		if (m_xp >= m_neededXP)
		{
			this->level_up();
		}
	}
}

Weapon* Character::set_weapon(Weapon* weapon)
{
	Weapon* save = m_weapon;
	m_weapon = weapon;
	return save;
}

void Character::level_up()
{
	while (m_xp >= m_neededXP)
	{
		m_level++;
		m_xp -= m_neededXP;
		m_neededXP = round(exp(log(1000) - 0.1) * exp(m_level * 0.1));
		m_speed *= 1.015;
		m_maxHealth *= exp(log(20) / 100.0);
		m_health *= exp(log(20) / 100.0);
		if (m_level % 5 == 0)
		{
			stat_up();
		}
		if (m_level % 10 == 0)
		{
			m_capacityLevel++;
		}
	}
	std::cout << ">>>" << m_name << " is now level " << m_level << "<<<" << std::endl << std::endl;
}

void Character::upload_level(int level, char type)
{
	for (int i = 0; i < level - 1; i++)
	{
		m_level++;
		m_neededXP = round(exp(log(1000) - 0.1) * exp(m_level * 0.1));
		m_speed *= 1.015;
		m_maxHealth *= exp(log(20) / 100.0);
		m_health *= exp(log(20) / 100.0);
		if (m_level % 5 == 0)
		{
			switch (type)
			{
			case 'b':
				m_defense += 5;
				m_attackBoost += 5;
				break;
			case 'j':
				m_defense += 10;
				break;
			case 's':
				m_attackBoost += 10;
				break;
			default:
				break;
			}
		}
		if (m_level % 10 == 0)
		{
			m_capacityLevel++;
		}
	}
}

void Character::attack_basic(Character* ennemy_target, bool bot)
{
	ennemy_target->take_damage(m_weapon->get_damage() + m_attackBoost);
	if (m_weapon->use() && !bot)
	{
		delete m_weapon;
		m_weapon = nullptr;
	}
}

std::string Character::get_weapon_type() const
{
	if (m_weapon == nullptr)
	{
		return "No weapon available";
	}
	return m_weapon->get_type();
}

void fight(Character* ally_character, Character* enemy_character)
{
	int choice_attack = -1;
	while (ally_character->is_alive() && enemy_character->is_alive())
	{
		if (ally_character->get_speed() >= enemy_character->get_speed())
		{
			std::cout << *enemy_character << *ally_character;
			std::cout << "Witch attack do you want to use :" << std::endl
				<< "[0]:Basic attack with your weapon (" << ally_character->get_weapon_type()
				<< ")" << std::endl
				<< "[1]:" << ally_character->get_attack_1() << std::endl
				<< "[2]:" << ally_character->get_attack_2() << std::endl;
			do
			{
				std::cout << ">>> ";
				std::cin >> choice_attack;
				if (choice_attack < 0 || choice_attack > 2)
				{
					std::cout << "<Invalide Choice>" << std::endl;
				}
				else
				{
					switch (choice_attack)
					{
					case 0:
						if (ally_character->m_weapon == nullptr)
						{
							std::cout << "<No weapon available>" << std::endl;
							choice_attack = -1;
						}
						else
						{
							std::cout << std::endl << ">>>You use basic attack<<<" << std::endl << std::endl;
							ally_character->attack_basic(enemy_character);
						}
						break;
					case 1:
						if (!ally_character->is_enough_mana(1))
						{
							std::cout << "<Not enough mana>" << std::endl;
							choice_attack = -1;
						}
						else
						{
							ally_character->attack_1(nullptr, enemy_character);
							std::cout << std::endl << ">>>You use "
								<< ally_character->get_attack_1(true) << "<<<" << std::endl << std::endl;
						}
						break;
					case 2:
						if (!ally_character->is_enough_mana(2))
						{
							std::cout << "<Not enough mana>" << std::endl;
							choice_attack = -1;
						}
						else
						{
							ally_character->attack_2(nullptr, enemy_character);
							std::cout << std::endl << ">>>You use "
								<< ally_character->get_attack_2(true) << "<<<" << std::endl << std::endl;
						}
						break;
					default:
						break;
					}
				}
			} while (choice_attack < 0 || choice_attack > 2);
			choice_attack = -1;
			if (enemy_character->is_alive())
			{
				while (choice_attack == -1)
				{
					choice_attack = rand() % 3;
					switch (choice_attack)
					{
					case 0:
						if (enemy_character->m_weapon->get_durability() == 0)
						{
							choice_attack = -1;
						}
						else
						{
							std::cout << std::endl << ">>>" << enemy_character->get_name()
								<< " use basic attack<<<" << std::endl << std::endl;
							enemy_character->attack_basic(ally_character, true);
						}
						break;
					case 1:
						if (!enemy_character->is_enough_mana(1))
						{
							choice_attack = -1;
						}
						else
						{
							enemy_character->attack_1(nullptr, ally_character);
							std::cout << std::endl << ">>>" << enemy_character->get_name() << " use "
								<< enemy_character->get_attack_1(true) << "<<<" << std::endl << std::endl;
						}
						break;
					case 2:
						if (!enemy_character->is_enough_mana(2))
						{
							choice_attack = -1;
						}
						else
						{
							enemy_character->attack_2(nullptr, ally_character);
							std::cout << std::endl << ">>>" << enemy_character->get_name() << " use "
								<< enemy_character->get_attack_2(true) << "<<<" << std::endl << std::endl;
						}
						break;
					default:
						break;
					}
				}
			}
			choice_attack = -1;
		}
		else
		{
			while (choice_attack == -1)
			{
				choice_attack = rand() % 3;
				switch (choice_attack)
				{
				case 0:
					if (enemy_character->m_weapon->get_durability() == 0)
					{
						choice_attack = -1;
					}
					else
					{
						std::cout << std::endl << ">>>" << enemy_character->get_name()
							<< " use basic attack<<<" << std::endl << std::endl;
						enemy_character->attack_basic(ally_character, true);
					}
					break;
				case 1:
					if (!enemy_character->is_enough_mana(1))
					{
						choice_attack = -1;
					}
					else
					{
						enemy_character->attack_1(nullptr, ally_character);
						std::cout << std::endl << ">>>" << enemy_character->get_name() << " use "
							<< enemy_character->get_attack_1(true) << "<<<" << std::endl << std::endl;
					}
					break;
				case 2:
					if (!enemy_character->is_enough_mana(2))
					{
						choice_attack = -1;
					}
					else
					{
						enemy_character->attack_2(nullptr, ally_character);
						std::cout << std::endl << ">>>" << enemy_character->get_name() << " use "
							<< enemy_character->get_attack_2(true) << "<<<" << std::endl << std::endl;
					}
					break;
				default:
					break;
				}
			}
			choice_attack = -1;
			if (ally_character->is_alive())
			{
				std::cout << *enemy_character << *ally_character;
				std::cout << "Witch attack do you want to use :" << std::endl
					<< "[0]:Basic attack with your weapon (" << ally_character->get_weapon_type()
					<< ")" << std::endl
					<< "[1]:" << ally_character->get_attack_1() << std::endl
					<< "[2]:" << ally_character->get_attack_2() << std::endl;
				do
				{
					std::cout << ">>> ";
					std::cin >> choice_attack;
					if (choice_attack < 0 || choice_attack > 2)
					{
						std::cout << "<Invalide Choice>" << std::endl;
					}
					else
					{
						switch (choice_attack)
						{
						case 0:
							if (ally_character->m_weapon == nullptr)
							{
								std::cout << "<No weapon available>" << std::endl;
								choice_attack = -1;
							}
							else
							{
								std::cout << std::endl << ">>>You use basic attack<<<" << std::endl << std::endl;
								ally_character->attack_basic(enemy_character);
							}
							break;
						case 1:
							if (!ally_character->is_enough_mana(1))
							{
								std::cout << "<Not enough mana>" << std::endl;
								choice_attack = -1;
							}
							else
							{
								ally_character->attack_1(nullptr, enemy_character);
								std::cout << std::endl << ">>>You use "
									<< ally_character->get_attack_1(true) << "<<<" << std::endl << std::endl;
							}
							break;
						case 2:
							if (!ally_character->is_enough_mana(2))
							{
								std::cout << "<Not enough mana>" << std::endl;
								choice_attack = -1;
							}
							else
							{
								ally_character->attack_2(nullptr, enemy_character);
								std::cout << std::endl << ">>>You use "
									<< ally_character->get_attack_2(true) << "<<<" << std::endl << std::endl;
							}
							break;
						default:
							break;
						}
					}
				} while (choice_attack < 0 || choice_attack > 2);
			}
			choice_attack = -1;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Character& character)
{
	character.stat(os);
	return os;
}