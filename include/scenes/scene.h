#pragma once

enum class SceneId {
  kNull,
  kMenu,
  kPlay,
  kPause,
  kEnding,
};

class Scene {
public:
  Scene(SceneId scene_id);
  virtual ~Scene();

  virtual void Update();
  virtual void Draw() const;
  virtual void OnEnter();
  virtual void OnExit();

private:
  SceneId scene_id_;
};
