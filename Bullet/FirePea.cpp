#include <allegro5/base.h>

#include "FirePea.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

FirePea::FirePea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
    Bullet("play/fire_pea.png", 250, 40, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    bulletType = BulletType::FIREPEA;
}

void FirePea::OnExplode(Zombie* enemy) {
}

