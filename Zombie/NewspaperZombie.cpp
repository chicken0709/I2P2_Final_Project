#include "NewspaperZombie.hpp"

NewspaperZombie::NewspaperZombie(int index,int x, int y) : Zombie("basiczombie",index,107,216,164,{47,24,36},"play/newspaper_zombie.png", x, y, 100, 10, 10, 500, 0.5) {
    zombieType = ZombieType::NEWSPAPER;
}
