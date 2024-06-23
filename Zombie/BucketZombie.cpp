#include "BucketZombie.hpp"

BucketZombie::BucketZombie(int index,int x, int y) : Zombie("bucketzombie",index,126,166,144,{47,40,39},"play/bucket_zombie.png", x, y, 100, 30, 30, 1300, 0.5) {
    zombieType = ZombieType::BUCKET;
}
