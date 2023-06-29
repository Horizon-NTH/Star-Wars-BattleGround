#pragma once

#include "Object.h"

#define NAME_ARMOR_NUMBER 20

class Armor :
    public Object
{
public:
    Armor(int level = 1, std::string name = "");
    int get_level() const;
    int get_defense() const;
    std::string get_type() const;

protected:
    int m_level;
    std::vector<std::string> m_nameList;

    void charge_name();
    void set_name();
    void stat(std::ostream& os) const;
    void boost(Character** character_array);
    void unboost(Character** character_array);
    char get_type_save() const;
};

