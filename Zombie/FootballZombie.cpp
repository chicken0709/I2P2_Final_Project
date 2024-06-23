#include "FootballZombie.hpp"

FootballZombie::FootballZombie(int index,int x, int y) : Zombie("basiczombie",index,84,154,172,{30,36,18},"play/football_zombie.png", x, y, 100, 40, 50, 1400, 0.5) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
