#include "FlagZombie.hpp"

FlagZombie::FlagZombie(int x, int y) : Zombie("basiczombie",index,47,83,72,{47},"play/flag_zombie.png", x, y, 100, 30, 30, 200, 0.5) {
    zombieType = ZombieType::BASIC_FLAG;
}
