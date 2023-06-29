#pragma once

#include "Object.h"

#define NAME_WEAPON_NUMBER 248

class Weapon :
    public Object
{
    friend class Inventory;
    friend class Character;
    friend class Planet;

public:
    Weapon();
    Weapon(int damage, int durability, std::string name = "", int maxDurability = -1);
    ~Weapon();
    int get_damage() const;
    int get_durability() const;
    int get_maxDurability() const;
    int get_level() const;
    std::string get_type() const;

protected:
    int m_damage, m_durability,
        m_maxDurability;
    std::vector<std::string> m_nameList;

    void charge_name();
    void set_name();
    void repare();
    bool is_usable() const;
    void stat(std::ostream& os) const;
    void boost(Character** character_array);
    void unboost(Character** character_array);
    bool use();
    char get_type_save() const;
};

