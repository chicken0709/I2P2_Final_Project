#include "BasicZombie.hpp"

BasicZombie::BasicZombie(int x, int y) : Zombie("play/basic_zombie.png", x, y, 100, 20, 20, 200, 0.5) {
    zombieType = ZombieType::BASIC_FLAG;
}
