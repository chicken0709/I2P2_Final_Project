#include "NewspaperZombie.hpp"

NewspaperZombie::NewspaperZombie(int x, int y) : Zombie("basiczombie",index,47,83,72,{47},"play/newspaper_zombie.png", x, y, 100, 30, 30, 500, 0.5) {
    zombieType = ZombieType::NEWSPAPER;
}
