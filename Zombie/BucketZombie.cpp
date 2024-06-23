#include "BucketZombie.hpp"

BucketZombie::BucketZombie(int x, int y) : Zombie("basiczombie",index,47,83,72,{47},"play/bucket_zombie.png", x, y, 100, 20, 20, 1300, 0.5) {
    zombieType = ZombieType::BUCKET;
}
