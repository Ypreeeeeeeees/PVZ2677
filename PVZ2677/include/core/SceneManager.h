#ifndef PVZ_SCENEMANAGER_H
#define PVZ_SCENEMANAGER_H

#include <unordered_map>
#include <memory>
#include "core/Scene.h"

class SceneManager {
public:
    SceneManager() = default;

    void RegisterScene(SceneID id, std::unique_ptr<Scene> scene);
    void SwitchTo(SceneID id);
    void Update(float dt);
    void Render();

    SceneID GetCurrentSceneID() const;
    bool IsTransitioning() const { return pendingTransition != SceneID::None; }

private:
    void PerformTransition();

    std::unordered_map<SceneID, std::unique_ptr<Scene>> scenes;
    Scene* currentScene = nullptr;
    SceneID pendingTransition = SceneID::None;
};

#endif // PVZ_SCENEMANAGER_H
