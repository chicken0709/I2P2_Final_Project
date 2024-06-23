#include "FootballZombie.hpp"

FootballZombie::FootballZombie(int x, int y) : Zombie("basiczombie",index,47,83,72,{47},"play/football_zombie.png", x, y, 100, 60, 60, 1400, 0.5) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
