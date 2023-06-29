#pragma once

#include "Object.h"

#define NAME_AMPLIFIER_NUMBER 47

typedef enum amplifier_type amplifier_type;
enum amplifier_type
{
	ATTACK = 0,
	HEALTH = 1,
	SPEED = 2
};

std::ostream& operator << (std::ostream& os, amplifier_type at);

class Amplifier :
	public Object
{
public:
	Amplifier(amplifier_type type, int level = 1, std::string name = "");
	~Amplifier();
	int get_boost() const;
	int get_level() const;
	std::string get_type() const;

protected:
	int m_level;
	amplifier_type m_type;
	std::vector<std::string> m_nameList;

	void charge_name();
	void set_name();
	void stat(std::ostream& os) const;
	void boost(Character** character_array);
	void unboost(Character** character_array);
	char get_type_save() const;
};

