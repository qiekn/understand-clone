#pragma once

#include <memory>
#include <unordered_map>
#include "scene.h"

class SceneManager {
public:
  SceneManager();
  virtual ~SceneManager();

  void Add(SceneId id, std::unique_ptr<Scene> scene);  // Add a scene to the map
  void Switch(SceneId id);  // Switch to a new scene if it exists
  void Update() const;
  void Draw() const;

private:
  SceneId current_scene_id_ = SceneId::kNull;
  std::unordered_map<SceneId, std::unique_ptr<Scene>> scenes_;
};
