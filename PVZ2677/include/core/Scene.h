#ifndef PVZ_SCENE_H
#define PVZ_SCENE_H

enum class SceneID {
    None,
    Splash,
    Menu,
    Gameplay,
    Pause,
    Victory,
    Defeat,
    Help,
    About,
    Settings
};

class Scene {
public:
    virtual ~Scene() = default;

    SceneID GetID() const { return sceneID; }

    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

protected:
    SceneID sceneID = SceneID::None;
};

#endif // PVZ_SCENE_H
