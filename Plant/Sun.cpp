#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/AudioHelper.hpp"

#include "Sun.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* Sun::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Sun::Sun(std::string img, Engine::Point position) : Sprite(img, position.x, position.y) {
}

void Sun::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();

    mouseIn = Engine::Collider::IsPointInBitmap(Engine::Point((mouse.x - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (mouse.y - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
    if (mouseIn) {
        getPlayScene()->EarnMoney(50);
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("sun_collect.mp3");
    }
}
