#include "Sith.h"

Sith::Sith(int level, const std::string name, Weapon* weapon, char type) :
	ForceUser(level, name, weapon, type)
{
	get_name();
	if (name == "")
	{
		set_name();
	}
}

Sith::~Sith()
{
}

bool Sith::is_enough_mana(int attack) const
{
	switch (attack)
	{
	case 1:
		return true;
		break;
	case 2:
		return m_mana >= 80;
		break;
	default:
		return false;
		break;
	}
}

void Sith::stat_up()
{
	m_attackBoost += 10;
}

void Sith::attack_1(Character* ally_target, Character* enemy_target)
{
	if (enemy_target != this && enemy_target != nullptr)
	{
		enemy_target->take_damage(m_capacityLevel * 10 + m_attackBoost);
		this->heal(m_capacityLevel * 10 + m_attackBoost);
		this->boost_attack(m_capacityLevel * 5);
		this->restore_mana(m_capacityLevel * 10);
	}
}

void Sith::attack_2(Character* ally_target, Character* enemy_target)
{
	if (enemy_target != this && enemy_target != nullptr)
	{
		enemy_target->take_damage(m_capacityLevel * 40 + m_attackBoost);
		this->decrease_mana(80);
	}
}

std::string Sith::get_attack_1(bool name) const
{
	if (name)
	{
		return "Drain force";
	}
	return "Drain force (You drain the health of the ennemy and you restore your mana)";
}

std::string Sith::get_attack_2(bool name) const
{
	if (name)
	{
		return "force crush";
	}
	return "Force crush (You deal damage to the ennemy and boost your attack) : cost 80 mana";
}

void Sith::get_name()
{
	std::ifstream stream("../assets/data/Sith.txt");
	std::string name;

	if (stream)
	{
		while (std::getline(stream, name))
		{
			m_nameList.push_back(name);
		}
	}
	else
	{
		std::cout << ">>>Error, please restart the game." << std::endl;
		exit(0);
	}
}

void Sith::set_name()
{
	m_name = m_nameList[rand() % NAME_SITH_NUMBER];
}

void Sith::stat(std::ostream& os) const
{
	os << std::endl
		<< m_name << " (Sith) stats: " << std::endl
		<< "\t-Level: " << m_level << std::endl
		<< "\t-Xp: " << m_xp << " / " << m_neededXP << std::endl
		<< "\t-Health: " << m_health << " / " << m_maxHealth << std::endl
		<< "\t-Mana: " << m_mana << " / " << m_maxMana << std::endl
		<< "\t-Speed: " << m_speed << std::endl
		<< "\t-Defense: " << m_defense << std::endl
		<< "\t-Attack boost: " << m_attackBoost;
	if (m_weapon != nullptr)
	{
		std::cout << *m_weapon << std::endl;
	}
	else
	{
		std::cout << "No weapon available" << std::endl << std::endl;
	}
}

char Sith::get_type_save() const
{
	return 's';
}
