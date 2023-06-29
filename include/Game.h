#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "MainPlayer.h"
#include "Planet.h"

class Game
{
	friend class Planet;

public:
	Game();
	~Game();
	void start_menu();
	void save();

private:
	MainPlayer* m_player;
	std::vector<Planet*> m_planets;

	void planet_generation();
	void player_generation();
	void print_title() const;
	void main_menu();
	void browse_planets();
	bool get_save();
};

