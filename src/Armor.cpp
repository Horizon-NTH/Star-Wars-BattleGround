#include "Armor.h"

Armor::Armor(int level, std::string name) :
	Object(name), m_level(level)
{
	charge_name();
	if (name == "")
	{
		set_name();
	}
}

int Armor::get_level() const
{
	return m_level;
}

int Armor::get_defense() const
{
	return m_level * 10;
}

std::string Armor::get_type() const
{
	return "Armor";
}

void Armor::charge_name()
{
	std::ifstream stream("../assets/data/Armor.txt");
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

void Armor::set_name()
{
	m_name = m_nameList[rand() % NAME_ARMOR_NUMBER];

}

void Armor::stat(std::ostream& os) const
{
	os << std::endl
		<< m_name << " (Armor) stats: " << std::endl
		<< "\t-Level: " << m_level << std::endl
		<< "\t-Defense boost: " << this->get_defense() << std::endl;
}

void Armor::boost(Character** character_array)
{
	for (int i = 0; i < 5; i++)
	{
		if (character_array[i] != nullptr)
		{
			character_array[i]->m_defense += get_defense();
		}
	}
}

void Armor::unboost(Character** character_array)
{
	for (int i = 0; i < 5; i++)
	{
		if (character_array[i] != nullptr)
		{
			character_array[i]->m_defense -= get_defense();
		}
	}
}

char Armor::get_type_save() const
{
	return 'a';
}
