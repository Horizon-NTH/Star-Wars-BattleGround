#pragma once

#include <iostream>
#include <string>

#include "Character.h"

class Object
{
	friend class Player;
	friend class Game;

public:
	Object(std::string name);
	virtual ~Object();
	std::string get_name();
	virtual int get_level() const = 0;
	virtual std::string get_type() const = 0;

protected:
	std::string m_name;

	virtual void stat(std::ostream& os) const = 0;
	virtual void boost(Character** character_array) = 0;
	virtual void unboost(Character** character_array) = 0;
	virtual char get_type_save() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Object& object);
};

