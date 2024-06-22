#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.hpp"
#include "Scene/SettingsScene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // Register scenes
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());

    // Start game
	game.Start("start", 60, 1600, 900);
	return 0;
}
