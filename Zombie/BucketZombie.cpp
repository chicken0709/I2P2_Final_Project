#include "BucketZombie.hpp"

BucketZombie::BucketZombie(int x, int y) : Zombie("play/bucket_zombie.png", x, y, 100, 20, 20, 1300, 0.5) {
    zombieType = ZombieType::BUCKET;
}
