#include "NewspaperZombie.hpp"

NewspaperZombie::NewspaperZombie(int index,int x, int y) : Zombie("basiczombie",index,191,216,164,{47,24,36,13,47,24},"play/newspaper_zombie.png", x, y, 100, 20, 20, 500, 0.5) {
    zombieType = ZombieType::NEWSPAPER;
}
