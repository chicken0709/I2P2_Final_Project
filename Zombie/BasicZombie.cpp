#include "BasicZombie.hpp"

BasicZombie::BasicZombie(int index,int x, int y) : Zombie("basiczombie",index,47,83,72,{47},"play/basic_zombie.png", x, y, 100, 50, 50, 200, 5,0.5) {
    zombieType = ZombieType::BASIC_FLAG;
}
