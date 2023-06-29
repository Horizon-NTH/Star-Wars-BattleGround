#include "NPC.h"

NPC::NPC(std::string name) :
	Player(name)
{
}

NPC::~NPC()
{
	Player::~Player();
}

void NPC::stat(std::ostream& os) const
{
	os << m_name << " (Boss) stats: " << std::endl
		<< *m_inventory;
}
