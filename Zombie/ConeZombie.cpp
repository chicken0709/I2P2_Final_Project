#include "ConeZombie.hpp"

ConeZombie::ConeZombie(int index,int x, int y) : Zombie("basiczombie",index,126,166,144,{47,40,39},"play/cone_zombie.png", x, y, 100, 30, 30, 560, 0.5) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
