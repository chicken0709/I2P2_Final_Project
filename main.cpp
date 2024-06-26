#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"

#include "Scene/PlayScene.hpp"
#include "Scene/MenuScene.hpp"
#include "Scene/StartScene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // Register scenes
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("menu", new MenuScene());
	game.AddNewScene("play", new PlayScene());

    // Start game
	game.Start("start", 60, 1600, 900);
	return 0;
}
