#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP
#include "Engine/IScene.hpp"

class MenuScene final : public Engine::IScene {
public:
	explicit MenuScene() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int mode);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // MENUSCENE_HPP
