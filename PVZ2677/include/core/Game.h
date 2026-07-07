#ifndef PVZ_GAME_H
#define PVZ_GAME_H

#include <memory>

class SceneManager;
class ResourceManager;
class InputManager;
class SoundManager;
class GameTimer;
class Config;

class Game {
public:
    static Game& GetInstance();

    bool Init(int width, int height, const wchar_t* title);
    void Run();
    void Quit();

    SceneManager&    GetSceneManager()    { return *sceneManager; }
    ResourceManager& GetResourceManager() { return *resourceManager; }
    InputManager&    GetInputManager()    { return *inputManager; }
    Config&          GetConfig()          { return *config; }
    GameTimer&       GetGameTimer()       { return *gameTimer; }
    bool             IsRunning() const    { return isRunning; }

private:
    Game() = default;
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    std::unique_ptr<SceneManager>    sceneManager;
    std::unique_ptr<ResourceManager> resourceManager;
    std::unique_ptr<InputManager>    inputManager;
    std::unique_ptr<Config>          config;
    std::unique_ptr<GameTimer>       gameTimer;
    bool isRunning = false;
};

#endif // PVZ_GAME_H
