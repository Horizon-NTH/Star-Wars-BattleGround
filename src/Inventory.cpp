#include "Inventory.h"

Inventory::Inventory() :
	m_level(1), m_character_array{ nullptr }, m_objectNumber(0), m_characterNumber(0)
{
}

Inventory::~Inventory()
{
	for (int i = 0; i < m_characterNumber; i++)
	{
		delete m_character_array[i];
	}
	for (int i = 0; i < m_objectNumber; i++)
	{
		delete m_object_array[i];
	}
}

int Inventory::get_weapon_durability_needed()
{
	int number = 0;
	for (int i = 0; i < m_characterNumber; i++)
	{
		if (m_character_array[i]->m_weapon != nullptr)
		{
			number += m_character_array[i]->m_weapon->m_maxDurability - m_character_array[i]->m_weapon->get_durability();
		}
	}
	return number;
}

void Inventory::repare_weapon()
{
	for (int i = 0; i < m_characterNumber; i++)
	{
		if (m_character_array[i]->m_weapon != nullptr)
		{
			m_character_array[i]->m_weapon->repare();
		}
	}
}

void Inventory::add_character(Character* character, bool bot)
{
	if (m_characterNumber < 5 && !this->is_character_in(character))
	{

		m_character_array[m_characterNumber] = character;
		m_characterNumber++;
		if (!bot)
		{
			if (m_characterNumber > 1)
			{
				std::cout << std::endl << "You have a new character: " << std::endl
					<< "\t-" << character->get_name()
					<< " (lvl: " << character->get_level() << ")" << std::endl << std::endl;
			}
			else
			{
				std::cout << std::endl << "You have your first character: " << std::endl
					<< "\t-" << character->get_name()
					<< " (lvl: " << character->get_level() << ")" << std::endl << std::endl;
			}
		}
	}
	else if (!this->is_character_in(character))
	{
		std::cout << "You had too many character. Please choose if you want" <<
			"the character that you will delete: " << std::endl
			<< "\t[0]:The new one: " << character->get_name()
			<< " (lvl: " << character->get_level() << ")" << std::endl;
		for (int i = 0; i < m_characterNumber; i++)
		{
			std::cout << "\t[" << i + 1 << "]: " << m_character_array[i]->get_name()
				<< " (lvl: " << m_character_array[i]->get_level() << ")" << std::endl;
		}
		int choice = -1;
		int confirm = -1;
		do
		{
			std::cout << ">>> ";
			std::cin >> choice;
			if (choice < 0 || choice > m_characterNumber)
			{
				std::cout << "<Invalide Choice>" << std::endl;
			}
			else
			{
				std::cout << "You are going to delete: " << std::endl;
				switch (choice)
				{
				case 0:
					std::cout << "\t-" << character->get_name()
						<< " (lvl: " << character->get_level() << ")" << std::endl;
					break;
				default:
					std::cout << "\t-" << m_character_array[choice - 1]->get_name()
						<< " (lvl: " << m_character_array[choice - 1]->get_level() << ")"
						<< std::endl;
					break;
				}
				std::cout << "Do you confirm ?" << std::endl
					<< "\t[1]: Yes" << std::endl
					<< "\t[0]: No" << std::endl;
				do
				{
					std::cout << ">>> ";
					std::cin >> confirm;
					if (confirm < 0 || confirm > 1)
					{
						std::cout << "<Invalide Choice>" << std::endl;
					}
				} while (confirm < 0 || confirm > 1);
			}
		} while (choice < 0 || choice > m_characterNumber);
		if (confirm)
		{
			switch (choice)
			{
			case 0:
				delete character;
				break;
			default:
				delete m_character_array[choice - 1];
				m_character_array[choice - 1] = character;
				break;
			}
		}
		else
		{
			this->add_character(character);
		}
	}
}

void Inventory::add_object(Object* object, bool bot)
{
	if (m_objectNumber < m_level && !this->is_object_in(object))
	{
		m_object_array.push_back(object);
		m_objectNumber++;
		if (!bot)
		{
			std::cout << std::endl << "You have a new object: " << std::endl
				<< "\t-" << object->get_name()
				<< " (" << object->get_type() << " lvl: " << object->get_level() << ")" << std::endl << std::endl;
		}
	}
	else if (!this->is_object_in(object))
	{
		std::cout << "You had too many object. Please choose if you want, " <<
			"the object that you will delete: " << std::endl
			<< "\t[0]:The new one: " << object->get_name()
			<< " (" << object->get_type() << " lvl: " << object->get_level() << ")" << std::endl;
		for (int i = 0; i < m_objectNumber; i++)
		{
			std::cout << "\t[" << i + 1 << "]: " << m_object_array[i]->get_name()
				<< " (" << m_object_array[i]->get_type() << " lvl: " << m_object_array[i]->get_level() << ")" << std::endl;
		}
		int choice = -1;
		int confirm = -1;
		do
		{
			std::cout << ">>> ";
			std::cin >> choice;
			if (choice < 0 || choice > m_objectNumber)
			{
				std::cout << "<Invalide Choice>" << std::endl;
			}
			else
			{
				std::cout << "You are going to delete: " << std::endl;
				switch (choice)
				{
				case 0:
					std::cout << "\t-" << object->get_name()
						<< " (" << object->get_type() << " lvl: " << object->get_level() << ")" << std::endl;
					break;
				default:
					std::cout << "\t-" << m_object_array[choice - 1]->get_name()
						<< " (" << m_object_array[choice - 1]->get_type() << " lvl: " << m_object_array[choice - 1]->get_level() << ")"
						<< std::endl;
					break;
				}
				std::cout << "Do you confirm ?" << std::endl
					<< "\t[1]: Yes" << std::endl
					<< "\t[0]: No" << std::endl;
				do
				{
					std::cout << ">>> ";
					std::cin >> confirm;
					if (confirm < 0 || confirm > 1)
					{
						std::cout << "<Invalide Choice>" << std::endl;
					}
				} while (confirm < 0 || confirm > 1);
			}
		} while (choice < 0 || choice > m_objectNumber);
		if (confirm)
		{
			switch (choice)
			{
			case 0:
				delete object;
				break;
			default:
				delete m_object_array[choice - 1];
				m_object_array[choice - 1] = object;
				break;
			}
		}
		else
		{
			this->add_object(object);
		}
	}
}

void Inventory::add_weapon(Weapon* weapon)
{
	std::cout << "Please choose if you want, " <<
		"the character that will receve this weapon: " << std::endl
		<< "\t[0]:Destroy the new one: " << weapon->get_name()
		<< " (" << weapon->get_type() << ")" << std::endl;
	for (int i = 0; i < m_characterNumber; i++)
	{
		std::cout << "\t[" << i + 1 << "]: " << m_character_array[i]->get_name()
			<< " (lvl: " << m_character_array[i]->get_level() << ")" << "-->"
			<< m_character_array[i]->m_weapon->get_name() 
			<< " (" << m_character_array[i]->m_weapon->get_type() << ")" << std::endl;
	}
	int choice = -1;
	int confirm = -1;
	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > m_characterNumber)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			std::cout << "You are going to delete the weapon: " << std::endl;
			switch (choice)
			{
			case 0:
				std::cout << "\t-" << weapon->get_name()
					<< " (" << weapon->get_type() << ")" << std::endl;
				break;
			default:
				std::cout << m_character_array[choice - 1]->get_name()
					<< " (lvl: " << m_character_array[choice - 1]->get_level() << ")" 
					<< "-->" << m_character_array[choice - 1]->m_weapon->get_name() 
					<< " (" << m_character_array[choice - 1]->m_weapon->get_type() << ")" 
					<< std::endl;
				break;
			}
			std::cout << "Do you confirm ?" << std::endl
				<< "\t[1]: Yes" << std::endl
				<< "\t[0]: No" << std::endl;
			do
			{
				std::cout << ">>> ";
				std::cin >> confirm;
				if (confirm < 0 || confirm > 1)
				{
					std::cout << "<Invalide Choice>" << std::endl;
				}
			} while (confirm < 0 || confirm > 1);
		}
	} while (choice < 0 || choice > m_characterNumber);
	if (confirm)
	{
		switch (choice)
		{
		case 0:
			delete weapon;
			break;
		default:
			delete m_character_array[choice - 1]->m_weapon;
			m_character_array[choice - 1]->m_weapon = weapon;
			break;
		}
	}
	else
	{
		this->add_weapon(weapon);
	}
}

void Inventory::delete_character(Character* character)
{
	for (int i = 0; i < 5; i++)
	{
		if (m_character_array[i] == character)
		{
			for (int j = i; j < 4; j++)
			{
				m_character_array[j] = m_character_array[j + 1];
			}
			m_character_array[4] = nullptr;
			m_characterNumber--;
		}
	}
}

void Inventory::delete_object(Object* object)
{
	for (int i = 0; i < m_objectNumber; i++)
	{
		if (m_object_array[i] == object)
		{
			for (int j = i; j < m_objectNumber - 1; j++)
			{
				m_object_array[j] = m_object_array[j + 1];
			}
			m_object_array.pop_back();
			m_objectNumber--;
		}
	}
}

bool Inventory::is_character_in(Character* character) const
{
	for (int i = 0; i < 5; i++)
	{
		if (m_character_array[i] == character)
		{
			return true;
		}
	}
	return false;
}

bool Inventory::is_object_in(Object* object) const
{
	for (int i = 0; i < m_objectNumber; i++)
	{
		if (m_object_array[i] == object)
		{
			return true;
		}
	}
	return false;
}

void Inventory::upgrade(int numberLevelAdd, bool bot)
{
	m_level += numberLevelAdd;
	if (!bot)
	{
		std::cout << std::endl << "Your inventory is now level: " << m_level << std::endl;
	}
}

void Inventory::stat(std::ostream& os) const
{
	os << "Inventory stats: " << std::endl
		<< "\t-Level: " << m_level << std::endl
		<< "->Characters: " << std::endl;

	for (int i = 0; i < m_characterNumber; i++)
	{
		if (m_character_array[i] != nullptr)
		{
			os << *m_character_array[i];
		}
	}

	os << "->Objects: " << std::endl;

	for (int i = 0; i < m_objectNumber; i++)
	{
		os << *m_object_array[i];
	}
}

std::ostream& operator<<(std::ostream& os, const Inventory& inventory)
{
	inventory.stat(os);
	return os;
}
