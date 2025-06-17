#include "scene-manager.h"
#include <raylib.h>
#include <unordered_map>
#include "scene.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

// clang-format off
void SceneManager::Add(SceneId id, std::unique_ptr<Scene> scene) {
  if (!scene) {
    TraceLog(LOG_ERROR, "SceneManager: Attempted to add null scene for ID: %d", id);
    return;
  }
  auto [it, inserted] = scenes_.emplace(id, std::move(scene));
  if (!inserted) {
    TraceLog(LOG_WARNING, "SceneManager: Scene ID %d already exists, replacing", id);
    it->second = std::move(scene);  // Replace existing scene
  }
  TraceLog(LOG_INFO, "SceneManager: Added scene with ID: %d", id);
}

void SceneManager::Switch(SceneId id) {
  if (scenes_.find(id) != scenes_.end()) {
    if (current_scene_id_ != SceneId::kNull) {
      scenes_[current_scene_id_]->OnExit();
    }
    current_scene_id_ = id;
    scenes_[current_scene_id_]->OnEnter();
    TraceLog(LOG_INFO, "SceneManager: Switched to scene ID: %d", id);
  } else {
    TraceLog(LOG_ERROR, "SceneManager: Cannot switch to invalid scene ID: %d", id);
  }
}

void SceneManager::Update() const {
  scenes_.at(current_scene_id_)->Update();
  auto it = scenes_.find(current_scene_id_);
  if (it != scenes_.end()) {
    it->second->Update();
  } else {
    TraceLog(LOG_ERROR, "Invalid scene ID: %d", current_scene_id_);
  }

}

void SceneManager::Draw() const {
  auto it = scenes_.find(current_scene_id_);
  if (it != scenes_.end()) {
    it->second->Draw();
  } else {
    TraceLog(LOG_ERROR, "SceneManager: Invalid scene ID: %d", current_scene_id_);
  }
}
