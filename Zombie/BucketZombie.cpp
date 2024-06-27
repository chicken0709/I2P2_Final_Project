#include "BucketZombie.hpp"

BucketZombie::BucketZombie(int x, int y) :
Zombie(
    "bucketzombie",
    126,
    166,
    144,
    {47,40,39},
    x,
    y,
    100,
    10,
    10,
    1300
) {
    zombieType = ZombieType::BUCKET;
}
