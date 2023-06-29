#include "Weapon.h"

Weapon::Weapon() :
	Object(""), m_damage(10), m_durability(10),
	m_maxDurability(10)
{
	charge_name();
	if (m_name == "")
	{
		set_name();
	}
}

Weapon::Weapon(int damage, int durability, std::string name, int maxDurability) :
	Object(name), m_damage(damage), m_durability(durability),
	m_maxDurability(durability)
{
	charge_name();
	if (name == "")
	{
		set_name();
	}
	if (maxDurability != -1)
	{
		m_maxDurability = maxDurability;
	}
}

Weapon::~Weapon()
{
}

int Weapon::get_damage() const
{
    return m_damage;
}

int Weapon::get_durability() const
{
    return m_durability;
}

int Weapon::get_maxDurability() const
{
	return m_maxDurability;
}

int Weapon::get_level() const
{
	return 0;
}

std::string Weapon::get_type() const
{
	return "damage : " + std::to_string(m_damage) + ", durability : " 
		+ std::to_string(m_durability) + " / " 
		+ std::to_string(m_maxDurability);
}

void Weapon::charge_name()
{
	std::ifstream stream("../assets/data/Weapon.txt");
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

void Weapon::set_name()
{
	m_name = m_nameList[rand() % NAME_WEAPON_NUMBER];
}

void Weapon::repare()
{
	m_durability = m_maxDurability;
}

bool Weapon::is_usable() const
{
	return !(m_durability == 0);
}

void Weapon::stat(std::ostream& os) const
{
	os << std::endl
		<< m_name << " (Weapon) stats: " << std::endl
		<< "\t-Damage: " << m_damage << std::endl
		<< "\t-Durability: " << m_durability << " / " << m_maxDurability << std::endl;
}

void Weapon::boost(Character** character_array)
{
	std::cout << "Not possible" << std::endl;
}

void Weapon::unboost(Character** character_array)
{
	std::cout << "Not possible" << std::endl;
}

bool Weapon::use()
{
	m_durability--;
	if (m_durability == 0)
	{
		std::cout << std::endl << ">>>Weapon Broken<<<" << std::endl << std::endl;
		return true;
	}
	return false;
}

char Weapon::get_type_save() const
{
	return '\0';
}
