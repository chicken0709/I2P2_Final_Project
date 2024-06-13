#ifndef PLANTBUTTON_HPP
#define PLANTBUTTON_HPP
#include <string>

#include "UI/Component/ImageButton.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;

class PlantButton : public Engine::ImageButton {
protected:
    PlayScene* getPlayScene();
public:
	int money;
	Engine::Sprite Base;
	Engine::Sprite Plant;
	PlantButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Plant, float x, float y, int money);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // PLANTBUTTON_HPP
