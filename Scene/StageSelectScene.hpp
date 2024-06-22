#ifndef STAGESELECTSCENE_HPP
#define STAGESELECTSCENE_HPP
#include "Engine/IScene.hpp"

class StageSelectScene final : public Engine::IScene {
public:
	explicit StageSelectScene() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // STAGESELECTSCENE_HPP
