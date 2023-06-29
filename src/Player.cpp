#include "Player.h"

Player::Player(std::string name) :
	m_name(name), m_inventory(nullptr)
{
	m_inventory = new Inventory();
}

Player::~Player()
{
	delete m_inventory;
}

std::string Player::get_name() const
{
	return m_name;
}

void Player::boost()
{
	for (int i = 0; i < m_inventory->m_objectNumber; i++)
	{
		m_inventory->m_object_array[i]->boost(m_inventory->m_character_array);
	}
}

void Player::unboost()
{
	for (int i = 0; i < m_inventory->m_objectNumber; i++)
	{
		m_inventory->m_object_array[i]->unboost(m_inventory->m_character_array);
	}
	for (int i = 0; i < m_inventory->m_characterNumber; i++)
	{
		m_inventory->m_character_array[i]->set_maxHealth();
		m_inventory->m_character_array[i]->set_maxMana();
	}
}

bool Player::add_character_alive() const
{
	for (int i = 0; i < m_inventory->m_characterNumber; i++)
	{
		if (m_inventory->m_character_array[i]->is_alive())
		{
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	player.stat(os);
	return os;
}
