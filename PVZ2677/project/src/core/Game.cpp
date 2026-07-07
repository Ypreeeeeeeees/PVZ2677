#include "core/Game.h"
#include "core/GameTimer.h"
#include "core/SceneManager.h"
#include "scene/SplashScene.h"
#include "scene/MenuScene.h"
#include "scene/HelpScene.h"
#include "scene/AboutScene.h"
#include "scene/SettingsScene.h"
#include "scene/GameplayScene.h"
#include "scene/PauseScene.h"
#include "scene/VictoryScene.h"
#include "scene/DefeatScene.h"
#include "system/InputManager.h"
#include "system/ResourceManager.h"
#include "utils/Config.h"
#include "utils/Constants.h"
#include <graphics.h>

Game& Game::GetInstance() {
    static Game instance;
    return instance;
}

Game::~Game() {
}

bool Game::Init(int width, int height, const wchar_t* title) {
    initgraph(width, height);
    SetWindowText(GetHWnd(), title);

    setbkcolor(RGB(0, 0, 0));
    cleardevice();

    config = std::make_unique<Config>();
    config->SetWindowTitle(title);

    gameTimer = std::make_unique<GameTimer>();
    inputManager = std::make_unique<InputManager>();
    resourceManager = std::make_unique<ResourceManager>();

    sceneManager = std::make_unique<SceneManager>();
    sceneManager->RegisterScene(SceneID::Splash,   std::make_unique<SplashScene>());
    sceneManager->RegisterScene(SceneID::Menu,     std::make_unique<MenuScene>());
    sceneManager->RegisterScene(SceneID::Gameplay, std::make_unique<GameplayScene>());
    sceneManager->RegisterScene(SceneID::Pause,    std::make_unique<PauseScene>());
    sceneManager->RegisterScene(SceneID::Victory,  std::make_unique<VictoryScene>());
    sceneManager->RegisterScene(SceneID::Defeat,   std::make_unique<DefeatScene>());
    sceneManager->RegisterScene(SceneID::Help,     std::make_unique<HelpScene>());
    sceneManager->RegisterScene(SceneID::About,    std::make_unique<AboutScene>());
    sceneManager->RegisterScene(SceneID::Settings, std::make_unique<SettingsScene>());

    sceneManager->SwitchTo(SceneID::Splash);

    isRunning = true;
    return true;
}

void Game::Run() {
    while (isRunning) {
        float dt = gameTimer->Tick();
        inputManager->Update();
        sceneManager->Update(dt);

        BeginBatchDraw();
        sceneManager->Render();
        EndBatchDraw();
    }
}

void Game::Quit() {
    isRunning = false;
}
