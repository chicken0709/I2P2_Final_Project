#include "BasicZombie.hpp"

BasicZombie::BasicZombie(int x, int y) :
Zombie(
    "basiczombie",
    126,
    166,
    144,
    {47,40,39},
    x, y,
    100,
    10,
    10,
    200
) {
    zombieType = ZombieType::BASIC_FLAG;
}
