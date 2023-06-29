#pragma once

#include "Player.h"

class MainPlayer :
    public Player
{
    friend class Planet;
    friend class Game;

public:
    MainPlayer(std::string name);
    ~MainPlayer();
    int get_money() const;

private:
    int m_money;
    void add_money(int money_add);
    void add_xp(int xp_add);
    void decrease_money(int money_decrease);
    void stat(std::ostream& os) const;
};

