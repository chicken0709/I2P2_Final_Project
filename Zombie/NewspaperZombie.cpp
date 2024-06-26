#include "NewspaperZombie.hpp"
#include "Engine/Resources.hpp"

NewspaperZombie::NewspaperZombie(int index,int x, int y) :
Zombie(
    "newspaperzombie",
    index,
    107,
    216,
    164,
    {47,24,36},
    x, y,
    100,
    10,
    10,
    500
) {
    zombieType = ZombieType::NEWSPAPER;
    rageSpriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_2.png");
}
