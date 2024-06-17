#include <allegro5/base.h>

#include "SnowPea.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

SnowPea::SnowPea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
        Bullet("play/snow_pea.png", 250, 20, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void SnowPea::OnExplode(Zombie* enemy) {
    enemy -> UpdateSpeed();
}

