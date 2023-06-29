#include "Planet.h"

Planet::Planet(std::string name, std::string boss_name, int difficulty, int numberCharacterMax) :
	m_name(name), m_boss(nullptr), m_difficulty(difficulty), m_numberObject(0),
	m_numberCharacter(0), m_numberCharacterMax(numberCharacterMax),
	m_training_character(nullptr), m_open(false)
{
	m_boss = new NPC(boss_name);
	m_boss->m_inventory->upgrade(difficulty - 1);
}

Planet::~Planet()
{

	delete m_boss;
}

std::string Planet::get_name() const
{
	return m_name;
}

bool Planet::open() const
{
	return m_open;
}

void Planet::add_jedi_boss(std::string name, int level,
	std::string weapon_name, int weapon_damage, int weapon_durability, char type)
{
	if (m_numberCharacter < m_numberCharacterMax)
	{
		Jedi* jedi = nullptr;
		Weapon* weapon = nullptr;
		weapon = new Weapon(weapon_damage, weapon_durability, weapon_name);
		jedi = new Jedi(level, name, weapon);
		m_boss->m_inventory->add_character(jedi);
		m_numberCharacter++;
	}
}

void Planet::add_sith_boss(std::string name, int level,
	std::string weapon_name, int weapon_damage, int weapon_durability, char type)
{
	if (m_numberCharacter < m_numberCharacterMax)
	{
		Sith* sith = nullptr;
		Weapon* weapon = nullptr;
		weapon = new Weapon(weapon_damage, weapon_durability, weapon_name);
		sith = new Sith(level, name, weapon, type);
		m_boss->m_inventory->add_character(sith);
		m_numberCharacter++;
	}
}

void Planet::add_bounty_hunter_boss(std::string name, int level,
	std::string weapon_name, int weapon_damage, int weapon_durability, char type)
{
	if (m_numberCharacter < m_numberCharacterMax)
	{
		BountyHunter* bountyHunter = nullptr;
		Weapon* weapon = nullptr;
		weapon = new Weapon(weapon_damage, weapon_durability, weapon_name);
		bountyHunter = new BountyHunter(level, name, weapon, type);
		m_boss->m_inventory->add_character(bountyHunter);
		m_numberCharacter++;
	}
}

void Planet::add_amplifier_boss(std::string name, int level, amplifier_type type)
{
	Amplifier* amplifier = nullptr;
	amplifier = new Amplifier(type, level, name);
	m_boss->m_inventory->add_object(amplifier);
}

void Planet::add_armor_boss(std::string name, int level)
{
	Armor* armor = nullptr;
	armor = new Armor(level, name);
	m_boss->m_inventory->add_object(armor);
}

void Planet::stat(std::ostream& os) const
{
	os << m_name << " (Planet) stats: " << std::endl
		<< "\t-Difficulty: " << m_difficulty << std::endl
		<< *m_boss << std::endl << "-Shop: ";
}

void Planet::shop(Game* game, MainPlayer* player)
{
	game->save();
	std::cout << std::endl << "Welcome on our shop what do you want to buy (You have "
		<< player->m_money << " $):" << std::endl
		<< "\t[0]:Character (Random type and a level between "
		<< (m_difficulty - 1) * 10 << "/" << (m_difficulty - 1) * 10 + 5 << ") : "
		<< m_difficulty * 1000 << " $" << std::endl
		<< "\t[1]:Armor (Random level between 1/" << m_difficulty << ") : "
		<< m_difficulty * 2500 << " $" << std::endl
		<< "\t[2]:Amplifier (Random type and a level between " << m_difficulty << ") : "
		<< m_difficulty * 3000 << " $" << std::endl
		<< "\t[3]:Level up inventory: " << player->m_inventory->m_level * 20000 << " $" << std::endl
		<< "\t[4]:Weapon: " << m_difficulty * 500 << " $" << std::endl
		<< "\t[5]:Repare all your weapon: "
		<< player->m_inventory->get_weapon_durability_needed() * 10 << " $" << std::endl
		<< "\t[6]:Give " << m_difficulty * 1000 << " xp to all your acharacters: 2000 $" << std::endl
		<< "\t[7]:Leave shop." << std::endl;

	int choice = -1;

	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > 7)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			switch (choice)
			{
			case 0:
				if (!enough_money(player, m_difficulty * 1000))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
				break;
			case 1:
				if (!enough_money(player, m_difficulty * 2500))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
				break;
			case 2:
				if (!enough_money(player, m_difficulty * 3000))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
				break;
			case 3:
				if (!enough_money(player, player->m_inventory->m_level * 20000))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
				break;
			case 4:
				if (!enough_money(player, m_difficulty * 500))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
			case 5:
				if (!enough_money(player, player->m_inventory->get_weapon_durability_needed() * 10))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
			case 6:
				if (!enough_money(player, 2000))
				{
					std::cout << "<Not enough money>" << std::endl;
					choice = -1;
				}
			default:
				break;
			}
		}
	} while (choice < 0 || choice > 7);
	int random = rand() % 3,
		level = rand() % 5 + (m_difficulty - 1) * 10 + 1,
		damage = rand() % 10 + m_difficulty * 10;
	Character* character = nullptr;
	Object* object = nullptr;
	Weapon* weapon = nullptr;
	switch (choice)
	{
	case 0:
		player->decrease_money(m_difficulty * 1000);
		switch (random)
		{
		case 0:
			character = new BountyHunter(level);
			break;
		case 1:
			character = new Jedi(level);
			break;
		case 2:
			character = new Sith(level);
			break;
		default:
			break;
		}
		player->m_inventory->add_character(character, false);
		shop(game, player);
		break;
	case 1:
		player->decrease_money(m_difficulty * 2500);
		object = new Armor(rand() % m_difficulty + 1);
		player->m_inventory->add_object(object, false);
		shop(game, player);
		break;
	case 2:
		player->decrease_money(m_difficulty * 3000);
		object = new Amplifier(amplifier_type(random), rand() % m_difficulty + 1);
		player->m_inventory->add_object(object, false);
		shop(game, player);
		break;
	case 3:
		player->decrease_money(player->m_inventory->m_level * 20000);
		player->m_inventory->upgrade(1, false);
		shop(game, player);
		break;
	case 4:
		player->decrease_money(m_difficulty * 500);
		weapon = new Weapon(damage, m_difficulty * 10);
		player->m_inventory->add_weapon(weapon);
		shop(game, player);
		break;
	case 5:
		player->decrease_money(player->m_inventory->get_weapon_durability_needed() * 10);
		player->m_inventory->repare_weapon();
		shop(game, player);
		break;
	case 6:
		player->decrease_money(2000);
		player->add_xp(m_difficulty * 1000);
		shop(game, player);
		break;
	case 7:
		explore(game, player);
		break;
	default:
		break;
	}
}

bool Planet::enough_money(MainPlayer* player, int money) const
{
	return player->m_money >= money;
}

void Planet::set_open()
{
	m_open = true;
}

void Planet::explore(Game* game, MainPlayer* player)
{
	game->save();
	std::cout << "Please choose what you want to do:" << std::endl
		<< "\t[0]:Challenge the boss: " << m_boss->get_name() << std::endl
		<< "\t[1]:See boss stat's" << std::endl
		<< "\t[2]:Random fight" << std::endl
		<< "\t[3]:Go to the shop" << std::endl
		<< "\t[4]:Back to browse the galaxy" << std::endl;

	int choice = -1;
	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > 4)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			switch (choice)
			{
			case 0:
				boss_fight(game, player);
				break;
			case 1:
				std::cout << *m_boss << std::endl;
				explore(game, player);
				break;
			case 2:
				random_fight(game, player);
				break;
			case 3:
				shop(game, player);
				break;
			case 4:
				game->browse_planets();
				break;
			default:
				break;
			}
		}
	} while (choice < 0 || choice > 4);
}

void Planet::random_fight(Game* game, MainPlayer* player)
{
	player->boost();
	int random = rand() % 3,
		level = rand() % 5 + (m_difficulty - 1) * 10 + 5,
		damage = rand() % 10 + m_difficulty * 10;
	Character* ally_character = nullptr, * enemy_target = nullptr;
	Weapon* weapon = nullptr;
	weapon = new Weapon(damage, m_difficulty * 10);
	switch (random)
	{
	case 0:
		enemy_target = new BountyHunter(level, "", weapon);
		break;
	case 1:
		enemy_target = new Jedi(level, "", weapon);
		break;
	case 2:
		enemy_target = new Sith(level, "", weapon);
		break;
	default:
		break;
	}

	std::cout << "You are fighting: " << std::endl << "\t-"
		<< enemy_target->get_name()
		<< " (lvl: " << enemy_target->get_level() << ")" << "-->"
		<< enemy_target->m_weapon->get_name()
		<< " (" << enemy_target->m_weapon->get_type() << ")" << std::endl
		<< "Please choose the character you want to send for this fight:" << std::endl;

	for (int i = 0; i < player->m_inventory->m_characterNumber; i++)
	{
		std::cout << "\t[" << i << "]: " << player->m_inventory->m_character_array[i]->get_name()
			<< " (lvl: " << player->m_inventory->m_character_array[i]->get_level() << ")" << "-->"
			<< player->m_inventory->m_character_array[i]->m_weapon->get_name()
			<< " (" << player->m_inventory->m_character_array[i]->m_weapon->get_type() << ")"
			<< std::endl;
	}
	int choice = -1, choice_attack = -1;
	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > player->m_inventory->m_characterNumber)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			ally_character = player->m_inventory->m_character_array[choice];
		}
	} while (choice < 0 || choice > player->m_inventory->m_characterNumber);
	int attack_boost = ally_character->get_attackBoost(),
		defense_boost = ally_character->get_defense();
	fight(ally_character, enemy_target);
	delete enemy_target;
	ally_character->m_attackBoost = attack_boost;
	ally_character->m_defense = defense_boost;
	int xp_max = 1000 * m_difficulty * log(m_difficulty + 1),
		xp = rand() % (xp_max - xp_max / 2 + 1) + xp_max / 2,
		money = rand() % (m_difficulty * 1000);
	if (ally_character->is_alive())
	{
		std::cout << "Well played you win: " << std::endl
			<< "\t-" << money << " $" << std::endl
			<< "\t-" << xp << " xp" << std::endl;
		ally_character->add_xp(xp);
		player->add_money(money);
	}
	else
	{
		std::cout << "Oh no you loose: " << std::endl
			<< "\t-" << money * 5 << " $" << std::endl;
		player->decrease_money(money * 5);
	}
	player->unboost();
	explore(game, player);
}

void Planet::boss_fight(Game* game, MainPlayer* player)
{
	player->boost();
	m_boss->boost();
	int ally_attack_boost = 0,
		ally_defense_boost = 0,
		enemy_characterNumber = 0;
	Character* ally_character = nullptr,
		* enemy_character = m_boss->m_inventory->m_character_array[enemy_characterNumber];
	int enemy_attack_boost = enemy_character->get_attackBoost(),
		enemy_defense_boost = enemy_character->get_defense();
	std::cout << "You are fighting: " << std::endl << "\t-"
		<< m_boss->get_name() << std::endl;
	while (player->add_character_alive() && m_boss->add_character_alive())
	{
		if (enemy_character->is_alive())
		{
			if (ally_character != nullptr)
			{
				ally_character->m_attackBoost = ally_attack_boost;
				ally_character->m_defense = ally_defense_boost;
			}
			std::cout << "He sent the character: "
				<< enemy_character->get_name()
				<< " (lvl: " << enemy_character->get_level() << ")" << "-->"
				<< enemy_character->m_weapon->get_name()
				<< " (" << enemy_character->m_weapon->get_type() << ")" << std::endl
				<< "Please choose character you want to send:" << std::endl;

			for (int i = 0; i < player->m_inventory->m_characterNumber; i++)
			{
				std::cout << "\t[" << i << "]: " << player->m_inventory->m_character_array[i]->get_name()
					<< " (lvl: " << player->m_inventory->m_character_array[i]->get_level() << ")" << "-->"
					<< player->m_inventory->m_character_array[i]->m_weapon->get_name()
					<< " (" << player->m_inventory->m_character_array[i]->m_weapon->get_type() << ")"
					<< std::endl;
			}
			int choice = -1, choice_attack = -1;
			do
			{
				std::cout << ">>> ";
				std::cin >> choice;
				if (choice < 0 || choice > player->m_inventory->m_characterNumber)
				{
					std::cout << "<Invalide Choice>" << std::endl;
				}
				else
				{
					ally_character = player->m_inventory->m_character_array[choice];
				}
			} while (choice < 0 || choice > player->m_inventory->m_characterNumber);

			ally_attack_boost = ally_character->get_attackBoost();
			ally_defense_boost = ally_character->get_defense();
		}
		else
		{
			enemy_characterNumber++;
			if (enemy_character != nullptr)
			{
				enemy_character->m_attackBoost = enemy_attack_boost;
				enemy_character->m_defense = enemy_defense_boost;
			}
			enemy_character = m_boss->m_inventory->m_character_array[enemy_characterNumber];
			enemy_attack_boost = enemy_character->get_attackBoost();
			enemy_defense_boost = enemy_character->get_defense();
		}
		fight(ally_character, enemy_character);
	}
	ally_character->m_attackBoost = ally_attack_boost;
	ally_character->m_defense = ally_defense_boost;
	enemy_character->m_attackBoost = enemy_attack_boost;
	enemy_character->m_defense = enemy_defense_boost;
	int xp = 1000 * m_difficulty * log(m_difficulty + 1),
		money = m_difficulty * 1000;
	if (player->add_character_alive())
	{
		std::cout << "Well played you win: " << std::endl
			<< "\t-" << money << " $" << std::endl
			<< "\t-" << xp << " xp" << std::endl;
		player->add_xp(xp);
		player->add_money(money);
		int i = 0;
		while (game->m_planets[i]->m_open)
		{
			i++;
		}
		game->m_planets[i]->set_open();
		std::cout << std::endl << "<You unlock " << game->m_planets[i]->get_name() << ">" << std::endl << std::endl;
	}
	else
	{
		std::cout << "Oh no you loose: " << std::endl
			<< "\t-" << money * 5 << " $" << std::endl;
		player->decrease_money(money * 5);
	}
	player->unboost();
	m_boss->unboost();
	m_boss->m_inventory->repare_weapon();
	explore(game, player);
}

std::ostream& operator<<(std::ostream& os, const Planet& planet)
{
	planet.stat(os);
	return os;
}
