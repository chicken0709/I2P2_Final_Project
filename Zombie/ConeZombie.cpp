#include "ConeZombie.hpp"

ConeZombie::ConeZombie(int x, int y) : Zombie("basiczombie",index,47,83,72,{47},"play/cone_zombie.png", x, y, 100, 30, 30, 560, 0.5) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
