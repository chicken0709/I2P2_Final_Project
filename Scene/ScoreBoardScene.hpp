#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"


class ScoreBoardScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<std::pair<int, std::string>> scoreboardData;
    int page = 0;
public:
	explicit ScoreBoardScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int stage);
    void PrevOnClick(int page);
    void NextOnClick(int page);
    void ReadScoreBoard();
    void ShowScoreBoardData(int page);
    void SortScoreBoardData();
};

#endif // SCOREBOARDSCENE_HPP
