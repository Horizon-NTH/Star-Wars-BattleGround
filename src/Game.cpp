#include "Game.h"

Game::Game() :
	m_player(nullptr)
{
	print_title();
	planet_generation();
	m_planets[0]->set_open();
}

Game::~Game()
{
	save();
	for (int i = 0; i < PLANET_NUMBER; i++)
	{
		delete m_planets[i];
	}
	delete m_player;
}

void Game::main_menu()
{
	std::cout << "Please choose what you want to do: " << std::endl
		<< "\t[0]:Browse the galaxy" << std::endl
		<< "\t[1]:See stats" << std::endl
		<< "\t[2]:Close App" << std::endl;

	int choice = -1;
	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > 2)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			switch (choice)
			{
			case 0:
				browse_planets();
				break;
			case 1:
				std::cout << *m_player << std::endl;
				main_menu();
				break;
			case 2:
				std::cout << "<App closing>" << std::endl;
				save();
				exit(0);
			default:
				break;
			}
		}
	} while (choice < 0 || choice > 2);
}

void Game::browse_planets()
{
	std::cout << "Please choose what you want to do (Planets with *** are locked " << std::endl
		<< "you need to beat the boss of the precedent planet to unlock it.): " << std::endl;
	for (int i = 0; i < PLANET_NUMBER; i++)
	{
		std::cout << "\t[" << i << "]: " << (m_planets[i]->open() ? m_planets[i]->get_name() : "***") << std::endl;
	}
	std::cout << "\t[" << PLANET_NUMBER << "]:Back to main menu" << std::endl;

	int choice = -1;
	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > PLANET_NUMBER)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			if (choice == PLANET_NUMBER)
			{
				main_menu();
			}
			else
			{
				if (m_planets[choice]->open())
				{
					m_planets[choice]->explore(this, m_player);
				}
				else
				{
					std::cout << "<Planet locked>" << std::endl;
					choice = -1;
				}
			}
		}
	} while (choice < 0 || choice > PLANET_NUMBER);
}

bool Game::get_save()
{
	std::string name;
	std::cout << "Please enter the name you had:" << std::endl << ">>> ";
	std::cin.ignore();
	std::getline(std::cin, name);
	std::ifstream stream(("../assets/saves/" + name + ".txt").c_str());
	if (stream)
	{
		int inventory_level, money, character_number, object_number, level, xp, damage, durability, 
			maxDurability, open;
		char character_type, object_type;
		std::string character_name, object_name, weapon_name;
		stream >> inventory_level >> money;
		MainPlayer* player = nullptr;
		player = new MainPlayer(name);
		player->add_money(money);
		player->m_inventory->upgrade(inventory_level - 1);
		Character* character = nullptr;
		Weapon* weapon = nullptr;
		Object* object = nullptr;
		for (int i = 0; i < PLANET_NUMBER; i++)
		{
			stream >> open;
			if (open)
			{
				m_planets[i]->set_open();
			}
		}
		stream >> character_number;
		for (int i = 0; i < character_number; i++)
		{
			stream >> character_type;
			stream.ignore();
			std::getline(stream, character_name);
			stream >> level >> xp;
			stream.ignore();
			std::getline(stream, weapon_name);
			stream>> damage >> durability
				>> maxDurability;
			weapon = new Weapon(damage, durability, weapon_name, maxDurability);
			switch (character_type)
			{
			case 'b':
				character = new BountyHunter(level, character_name, weapon, character_type);
				character->add_xp(xp);
				break;
			case 'j':
				character = new Jedi(level, character_name, weapon, character_type);
				character->add_xp(xp);
				break;
			case 's':
				character = new Sith(level, character_name, weapon, character_type);
				character->add_xp(xp);
				break;
			default:
				break;
			}
			player->m_inventory->add_character(character);
			character = nullptr;
			weapon = nullptr;
		}
		stream >> object_number;
		for (int i = 0; i < object_number; i++)
		{
			stream >> object_type;
			stream.ignore();
			std::getline(stream, object_name);
			stream >> level;
			switch (object_type)
			{
			case 'a':
				object = new Armor(level, object_name);
				player->m_inventory->add_object(object);
				break;
			case 't':
				object = new Amplifier(ATTACK, level, object_name);
				player->m_inventory->add_object(object);
				break;
			case 'h':
				object = new Amplifier(HEALTH, level, object_name);
				player->m_inventory->add_object(object);
				break;
			case 's':
				object = new Amplifier(SPEED, level, object_name);
				player->m_inventory->add_object(object);
				break;
			default:
				break;
			}
			object = nullptr;
		}
		m_player = player;
		return true;
	}
	else
	{
		return false;
	}
}

void Game::save()
{
	std::ofstream stream(("../assets/saves/" + m_player->get_name() + ".txt").c_str());
	if (stream)
	{
		stream << m_player->m_inventory->m_level << std::endl
			<< m_player->get_money() << std::endl;
		for (int i = 0; i < PLANET_NUMBER; i++)
		{
			stream << m_planets[i]->m_open << std::endl;
		}
		stream	<< m_player->m_inventory->m_characterNumber << std::endl;
		for (int i = 0; i < m_player->m_inventory->m_characterNumber; i++)
		{
			stream << m_player->m_inventory->m_character_array[i]->get_type_save() << std::endl
				<< m_player->m_inventory->m_character_array[i]->get_name() << std::endl
				<< m_player->m_inventory->m_character_array[i]->get_level() << std::endl
				<< m_player->m_inventory->m_character_array[i]->m_xp << std::endl
				<< m_player->m_inventory->m_character_array[i]->m_weapon->get_name() << std::endl
				<< m_player->m_inventory->m_character_array[i]->m_weapon->get_damage() << std::endl
				<< m_player->m_inventory->m_character_array[i]->m_weapon->get_durability() << std::endl
				<< m_player->m_inventory->m_character_array[i]->m_weapon->get_maxDurability() << std::endl;
		}
		stream << m_player->m_inventory->m_objectNumber << std::endl;
		for (int i = 0; i < m_player->m_inventory->m_objectNumber; i++)
		{
			stream << m_player->m_inventory->m_object_array[i]->get_type_save() << std::endl
				<< m_player->m_inventory->m_object_array[i]->get_name() << std::endl
				<< m_player->m_inventory->m_object_array[i]->get_level() << std::endl;
		}
	}
}

void Game::planet_generation()
{
	std::ifstream stream("../assets/data/Planets.txt");
	if (stream)
	{
		for (int i = 0; i < PLANET_NUMBER; i++)
		{
			Planet* planet = nullptr;
			std::string planet_name, boss_name;
			int planet_difficulty, planet_numberCharacterMax;

			std::getline(stream, planet_name);
			std::getline(stream, boss_name);
			stream >> planet_difficulty >> planet_numberCharacterMax;

			planet = new Planet(planet_name, boss_name, planet_difficulty, planet_numberCharacterMax);

			for (int i = 0; i < planet_numberCharacterMax; i++)
			{
				std::string character_name, weapon_name;
				char character_type;
				int weapon_damage, weapon_durability;
				stream >> character_type;

				stream.ignore();
				std::getline(stream, character_name);
				std::getline(stream, weapon_name);

				stream >> weapon_damage >> weapon_durability;

				switch (character_type)
				{
				case 'b':
					planet->add_bounty_hunter_boss(character_name, planet_difficulty * 10,
						weapon_name, weapon_damage, weapon_durability);
					break;
				case 'j':
					planet->add_jedi_boss(character_name, planet_difficulty * 10,
						weapon_name, weapon_damage, weapon_durability);
					break;
				case 's':
					planet->add_sith_boss(character_name, planet_difficulty * 10,
						weapon_name, weapon_damage, weapon_durability);
					break;
				default:
					break;
				}
			}
			for (int i = 0; i < planet_difficulty; i++)
			{
				std::string object_name;
				char object_type;

				stream >> object_type;
				stream.ignore();
				std::getline(stream, object_name);

				switch (object_type)
				{
				case 'a':
					planet->add_armor_boss(object_name, planet_difficulty);
					break;
				case 't':
					planet->add_amplifier_boss(object_name, planet_difficulty, ATTACK);
					break;
				case 'h':
					planet->add_amplifier_boss(object_name, planet_difficulty, HEALTH);
					break;
				case 's':
					planet->add_amplifier_boss(object_name, planet_difficulty, SPEED);
					break;
				default:
					break;
				}
			}
			std::getline(stream, planet_name);

			m_planets.push_back(nullptr);
			m_planets[i] = planet;
		}
	}
	else
	{
		std::cout << ">>>Error, please restart the game." << std::endl;
		exit(0);
	}
}

void Game::player_generation()
{
	std::string name;
	std::cout << "Please enter your name:" << std::endl << ">>> ";
	std::cin.ignore();
	std::getline(std::cin, name);
	m_player = new MainPlayer(name);
	Character* character = nullptr;
	int random = rand() % 3;
	switch (random)
	{
	case 0:
		character = new BountyHunter();
		break;
	case 1:
		character = new Jedi();
		break;
	case 2:
		character = new Sith();
		break;
	default:
		break;
	}
	m_player->m_inventory->add_character(character, false);
}

void Game::print_title() const
{
	std::ifstream stream("../assets/data/Title.txt");
	std::string line;

	if (stream)
	{
		while (std::getline(stream, line))
		{
			std::cout << line << std::endl;
		}
	}
	else
	{
		std::cout << ">>>Error, please restart the game." << std::endl;
		exit(0);
	}
}

void Game::start_menu()
{
	std::cout << "Please choose what you want to do: " << std::endl
		<< "\t[0]:New Game" << std::endl
		<< "\t[1]:Continue Game" << std::endl
		<< "\t[2]:Credit" << std::endl
		<< "\t[3]:Close App" << std::endl;

	int choice = -1;
	do
	{
		std::cout << ">>> ";
		std::cin >> choice;
		if (choice < 0 || choice > 3)
		{
			std::cout << "<Invalide Choice>" << std::endl;
		}
		else
		{
			switch (choice)
			{
			case 0:
				player_generation();
				main_menu();
				break;
			case 1:
				if (get_save())
				{
					main_menu();
				}
				else
				{
					std::cout << "<No save at this name>" << std::endl;
					choice = -1;
				}
				break;
			case 2:
				std::cout << ">>>Made by Horizon<<<" << std::endl;
				choice = -1;
				break;
			case 3:
				std::cout << "<App closing>" << std::endl;
				exit(0);
			default:
				break;
			}
		}
	} while (choice < 0 || choice > 3);
}
