#include "ConeZombie.hpp"

ConeZombie::ConeZombie(int x, int y) : Zombie("play/cone_zombie.png", x, y, 100, 20, 20, 560, 0.5) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
