#include "BountyHunter.h"

BountyHunter::BountyHunter(int level, const std::string name, Weapon* weapon, char type) :
	Character(level, name, weapon, type)
{
	get_name();
	if (name == "")
	{
		set_name();
	}
}

BountyHunter::~BountyHunter()
{
}

bool BountyHunter::is_enough_mana(int attack) const
{
	return true;
}

void BountyHunter::stat_up()
{
	m_defense += 5;
	m_attackBoost += 5;
}

void BountyHunter::attack_1(Character* ally_target, Character* enemy_target)
{
	this->heal(m_capacityLevel * 20);
	this->reinforcement(m_capacityLevel * 5);
}

void BountyHunter::attack_2(Character* ally_target, Character* enemy_target)
{
	enemy_target->take_damage(m_capacityLevel * 30 + m_attackBoost);
	this->boost_attack(m_capacityLevel * 5);
	this->m_health -= m_capacityLevel * 10;
	if (this->m_health < 0)
	{
		this->m_health = 0;
	}
}

std::string BountyHunter::get_attack_1(bool name) const
{
	if (name)
	{
		return "Predator instinct";
	}
	return "Predator instinct (You heal yourself and boost your defense)";
}

std::string BountyHunter::get_attack_2(bool name) const
{
	if (name)
	{
		return "Execution";
	}
	return "Execution (You deal mass damage to the ennemy and gain attack but you also take some damage)";
}

void BountyHunter::get_name()
{
	std::ifstream stream("../assets/data/BountyHunter.txt");
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

void BountyHunter::set_name()
{
	m_name = m_nameList[rand() % NAME_BOUNTYHUNTER_NUMBER];
}

void BountyHunter::set_maxMana()
{
}

void BountyHunter::stat(std::ostream& os) const
{
	os << std::endl
		<< m_name << " (BountyHunter) stats: " << std::endl
		<< "\t-Level: " << m_level << std::endl
		<< "\t-Xp: " << m_xp << " / " << m_neededXP << std::endl
		<< "\t-Health: " << m_health << " / " << m_maxHealth << std::endl
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

char BountyHunter::get_type_save() const
{
	return 'b';
}

