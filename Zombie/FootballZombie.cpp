#include "FootballZombie.hpp"

FootballZombie::FootballZombie(int index,int x, int y) :
Zombie(
    "footballzombie",
    index,
    84,
    154,
    172,
    {30,36,18},
    x, y,
    100,
    30,
    30,
    1400
) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
