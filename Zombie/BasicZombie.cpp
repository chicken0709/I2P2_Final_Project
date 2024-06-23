#include "BasicZombie.hpp"

BasicZombie::BasicZombie(int index,int x, int y) : Zombie("basiczombie",index,126,166,144,{47,40,39},"play/basic_zombie.png", x, y, 100, 10, 10, 200, 0.5) {
    zombieType = ZombieType::BASIC_FLAG;
}
