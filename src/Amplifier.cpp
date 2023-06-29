#include "Amplifier.h"

Amplifier::Amplifier(amplifier_type type, int level, std::string name) :
	Object(name), m_level(level), m_type(type)
{
	charge_name();
	if (name == "")
	{
		set_name();
	}
}

Amplifier::~Amplifier()
{
}

int Amplifier::get_boost() const
{
	if (m_type == ATTACK)
	{
		return m_level * 10;
	}
	else if (m_type == HEALTH)
	{
		return m_level * 50;
	}
	else if (m_type == SPEED)
	{
		return m_level * 20;
	}
	return 0;
}

int Amplifier::get_level() const
{
	return m_level;
}

std::string Amplifier::get_type() const
{
	if (m_type == ATTACK)
	{
		return "Attack Amplifier";
	}
	else if (m_type == HEALTH)
	{
		return "Health Amplifier";
	}
	else if (m_type == SPEED)
	{
		return "Speed Amplifier";
	}
	return "";
}

void Amplifier::charge_name()
{
	std::ifstream stream("../assets/data/Amplifier.txt");
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

void Amplifier::set_name()
{
	m_name = m_nameList[rand() % NAME_AMPLIFIER_NUMBER];
}

void Amplifier::stat(std::ostream& os) const
{
	os << std::endl
		<< m_name << "(" << m_type << " amplifier) stats:" << std::endl
		<< "\t-Level: " << m_level << std::endl
		<< "\t-Boost: " << this->get_boost() << std::endl;
}

void Amplifier::boost(Character** character_array)
{
	for (int i = 0; i < 5; i++)
	{
		if (character_array[i] != nullptr)
		{
			if (m_type == ATTACK)
			{
				character_array[i]->m_attackBoost += get_boost();
			}
			else if (m_type == HEALTH)
			{
				character_array[i]->m_health += get_boost();
			}
			else if (m_type == SPEED)
			{
				character_array[i]->m_speed += get_boost();
			}
		}
	}
}

void Amplifier::unboost(Character** character_array)
{
	for (int i = 0; i < 5; i++)
	{
		if (character_array[i] != nullptr)
		{
			if (m_type == ATTACK)
			{
				character_array[i]->m_attackBoost -= get_boost();
			}
			else if (m_type == HEALTH)
			{
				character_array[i]->set_maxHealth();
			}
			else if (m_type == SPEED)
			{
				character_array[i]->m_speed -= get_boost();
			}
		}
	}
}

char Amplifier::get_type_save() const
{
	if (m_type == ATTACK)
	{
		return 't';
	}
	else if (m_type == HEALTH)
	{
		return 'h';
	}
	else if (m_type == SPEED)
	{
		return 's';
	}
	return NULL;
}

std::ostream& operator<<(std::ostream& os, amplifier_type at)
{
	const std::string nameAmplifier[] = { "Attack", "health", "Speed" };
	return os << nameAmplifier[at];
}
