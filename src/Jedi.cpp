#include "Jedi.h"

Jedi::Jedi(int level, const std::string name, Weapon* weapon, char type) :
	ForceUser(level, name, weapon, type)
{
	get_name();
	if (name == "")
	{
		set_name();
	}
}

Jedi::~Jedi()
{
}

bool Jedi::is_enough_mana(int attack) const
{
	switch (attack)
	{
	case 1:
		return m_mana >= 100;
		break;
	case 2:
		return true;
		break;
	default:
		return false;
		break;
	}
}

void Jedi::stat_up()
{
	m_defense += 10;
}

void Jedi::attack_1(Character* ally_target, Character* enemy_target)
{
	if (ally_target != this && ally_target != nullptr)
	{
		ally_target->heal(m_capacityLevel * 50);
		this->decrease_mana(100);
	}
	else
	{
		this->heal(m_capacityLevel * 50);
		m_mana -= 100;
	}
}

void Jedi::attack_2(Character* ally_target, Character* enemy_target)
{
	if (ally_target != this && ally_target != nullptr)
	{
		ally_target->reinforcement(m_capacityLevel * 5);
		ally_target->boost_attack(m_capacityLevel * 5);
		this->reinforcement(m_capacityLevel * 5);
		this->boost_attack(m_capacityLevel * 5);
		this->restore_mana(m_capacityLevel * 10);
	}
	else
	{
		this->reinforcement(m_capacityLevel * 5);
		this->boost_attack(m_capacityLevel * 5);
		this->restore_mana(m_capacityLevel * 10);
	}
}

std::string Jedi::get_attack_1(bool name) const
{
	if (name)
	{
		return "Force healing";
	}
	return "Force healing (Heal an ally target) : cost 100 mana";
}

std::string Jedi::get_attack_2(bool name) const
{
	if (name)
	{
		return "Soresu";
	}
	return "Soresu (Your character and another ally character gain defense and attack and you restor your mana)";
}

void Jedi::get_name()
{
	std::ifstream stream("../assets/data/Jedi.txt");
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

void Jedi::set_name()
{
	m_name = m_nameList[rand() % NAME_JEDI_NUMBER];
}

void Jedi::stat(std::ostream& os) const
{
	os << std::endl
		<< m_name << " (Jedi) stats: " << std::endl
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

char Jedi::get_type_save() const
{
	return 'j';
}
