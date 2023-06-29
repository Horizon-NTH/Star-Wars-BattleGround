#pragma once

#include "Player.h"

class NPC :
    public Player
{
    friend class Planet;

public:
    NPC(std::string name);
    ~NPC();

private:
    void stat(std::ostream& os) const;
};

