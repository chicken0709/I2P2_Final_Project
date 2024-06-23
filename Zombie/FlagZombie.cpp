#include "FlagZombie.hpp"

FlagZombie::FlagZombie(int index,int x, int y) : Zombie("basiczombie",index,126,166,144,{47,40,39},"play/flag_zombie.png", x, y, 100, 20, 20, 200, 0.5) {
    zombieType = ZombieType::BASIC_FLAG;
}
