#include "NewspaperZombie.hpp"

NewspaperZombie::NewspaperZombie(int x, int y) : Zombie("play/newspaper_zombie.png", x, y, 100, 20, 20, 500, 0.5) {
    zombieType = ZombieType::NEWSPAPER;
}
