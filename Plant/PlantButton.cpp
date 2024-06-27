#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"

#include "PlantButton.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* PlantButton::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

PlantButton::PlantButton(
	std::string img,
	std::string imgIn,
	Engine::Sprite Base,
	Engine::Sprite Plant,
	float x, float y,
	int money
) :
	ImageButton(img, imgIn, x, y), money(money), Base(Base), Plant(Plant) {
}

void PlantButton::Update(float deltaTime) {
	ImageButton::Update(deltaTime);
	if (getPlayScene()->GetMoney() >= money) {
		Enabled = true;
	} else {
		Enabled = false;
	}
}

void PlantButton::Draw() const {
	ImageButton::Draw();
	Base.Draw();
	Plant.Draw();
}
