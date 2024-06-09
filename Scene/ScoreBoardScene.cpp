#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "ScoreBoardScene.hpp"

void ScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    ReadScoreBoard();
    SortScoreBoardData();

    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, 100, 10, 255, 100, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("PAGE " + std::to_string(page + 1), "pirulen.ttf", 48, halfW + 500, 100, 10, 255, 100, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH + 250, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH + 300, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH + 250, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevOnClick, this, page));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("PREV", "pirulen.ttf", 48, halfW - 500, halfH + 300, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH + 250, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextOnClick, this, page));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("NEXT", "pirulen.ttf", 48, halfW + 500, halfH + 300, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);

    ShowScoreBoardData(page);
}

void ScoreBoardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}

void ScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreBoardScene::PrevOnClick(int currentPage) {
    if(currentPage != 0) page--;
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
}

void ScoreBoardScene::NextOnClick(int currentPage) {
    page++;
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
}

void ScoreBoardScene::ReadScoreBoard() {
    std::string filename = std::string("Resource/scoreboard.txt");
    // Read enemy file.
    std::string name;
    int lives;
    scoreboardData.clear();
    std::ifstream fin(filename);
    while (fin >> name && fin >> lives) {
        scoreboardData.emplace_back(lives, name);
    }
    fin.close();
}

void ScoreBoardScene::ShowScoreBoardData(int page) {
    int startIdx = page * 6;
    if(startIdx >= scoreboardData.size()) return;
    for(int i = 0; i < 6 && i + startIdx < scoreboardData.size(); i++) {
        AddNewObject(new Engine::Label(scoreboardData[i + startIdx].second, "pirulen.ttf", 32, 650, 275 + 50 * i, 255, 255, 255, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label(std::to_string(scoreboardData[i + startIdx].first), "pirulen.ttf", 32, 1000, 275 + 50 * i, 255, 255, 255, 255, 0.5, 0.5));
    }
}

void ScoreBoardScene::SortScoreBoardData() {
    std::sort(scoreboardData.begin(), scoreboardData.end(), std::greater<std::pair<int, std::string>>());
}