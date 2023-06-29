#include "ForceUser.h"

ForceUser::ForceUser(int level, const std::string name, Weapon* weapon, char type) :
	Character(level, name, weapon, type), 
	m_mana(200), m_maxMana(200)
{
}

ForceUser::~ForceUser()
{
}

int ForceUser::get_mana() const
{
	return m_mana;
}

void ForceUser::restore_mana(int mana_restored)
{
	if (mana_restored > 0)
	{
		m_mana += mana_restored;
		if (m_mana > m_maxMana)
		{
			m_mana = m_maxMana;
		}
	}
}

void ForceUser::set_maxMana()
{
	m_mana = m_maxMana;
}

void ForceUser::decrease_mana(int mana_decrease)
{
	if (mana_decrease > 0)
	{
		m_mana -= mana_decrease;
		if (m_mana < 0)
		{
			m_mana = 0;
		}
	}
}
