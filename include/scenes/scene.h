#pragma once

enum class SceneId {
  kNull,
  kTest,
  kMenu,
  kPlay,
  kPause,
  kEnding,
};

class Scene {
public:
  Scene(SceneId scene_id);
  virtual ~Scene();

  virtual void Start();
  virtual void Update();
  virtual void Draw() const;
  virtual void End();

  /* animated transition */
  virtual void OnEnter();
  virtual void OnExit();

private:
  SceneId scene_id_;
};
