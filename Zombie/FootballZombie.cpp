#include "FootballZombie.hpp"

FootballZombie::FootballZombie(int x, int y) : Zombie("play/football_zombie.png", x, y, 100, 40, 40, 1400, 0.5) {
    zombieType = ZombieType::CONE_FOOTBALL;
}
