#include "core/SceneManager.h"

void SceneManager::RegisterScene(SceneID id, std::unique_ptr<Scene> scene) {
    scenes[id] = std::move(scene);
}

void SceneManager::SwitchTo(SceneID id) {
    pendingTransition = id;
}

void SceneManager::Update(float dt) {
    if (pendingTransition != SceneID::None) {
        PerformTransition();
    }
    if (currentScene) {
        currentScene->Update(dt);
    }
}

void SceneManager::Render() {
    if (currentScene) {
        currentScene->Render();
    }
}

SceneID SceneManager::GetCurrentSceneID() const {
    if (currentScene) {
        return currentScene->GetID();
    }
    return SceneID::None;
}

void SceneManager::PerformTransition() {
    if (pendingTransition == SceneID::None) return;

    auto it = scenes.find(pendingTransition);
    if (it == scenes.end()) {
        pendingTransition = SceneID::None;
        return;
    }

    if (currentScene) {
        currentScene->OnExit();
    }

    currentScene = it->second.get();
    currentScene->OnEnter();

    pendingTransition = SceneID::None;
}
