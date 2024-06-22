#include "FlagZombie.hpp"

FlagZombie::FlagZombie(int x, int y) : Zombie("play/flag_zombie.png", x, y, 100, 20, 20, 200, 0.5) {
    zombieType = ZombieType::BASIC_FLAG;
}
