#include "ConeZombie.hpp"

ConeZombie::ConeZombie(int x, int y) :
Zombie(
    "conezombie",
    126,
    166,
    144,
    {47,40,39},
    x,
    y,
    100,
    10,
    10,
    560
) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
