#include "MainPlayer.h"

MainPlayer::MainPlayer(std::string name) :
	Player(name), m_money(0)
{
}

MainPlayer::~MainPlayer()
{
	Player::~Player();
}

int MainPlayer::get_money() const
{
	return m_money;
}

void MainPlayer::add_money(int money_add)
{
	if (money_add > 0)
	{
		m_money += money_add;
	}
}

void MainPlayer::add_xp(int xp_add)
{
	for (int i = 0; i < m_inventory->m_characterNumber; i++)
	{
		m_inventory->m_character_array[i]->add_xp(xp_add);
	}
}

void MainPlayer::decrease_money(int money_decrease)
{
	if (money_decrease > 0)
	{
		m_money -= money_decrease;
		if (m_money < 0)
		{
			m_money = 0;
		}
	}
}

void MainPlayer::stat(std::ostream& os) const
{
	os << std::endl << m_name << " (Player) stats: " << std::endl
		<< "\t-Money: " << m_money << std::endl
		<< *m_inventory;
}
