#ifndef PVZ_GAME_H
#define PVZ_GAME_H

#include <memory>

enum class Difficulty {
    Easy = 0,
    Hard = 1,
    Hell = 2
};

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
    Difficulty       GetDifficulty() const { return difficulty; }
    void             SetDifficulty(Difficulty d) { difficulty = d; }
    void             SetVictoryInfo(int mowers) { remainingMowers = mowers; }
    int              GetRemainingMowers() const { return remainingMowers; }
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
    Difficulty difficulty = Difficulty::Easy;
    int remainingMowers = 0;
    bool isRunning = false;
};

#endif // PVZ_GAME_H
