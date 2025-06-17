#include "scene.h"
#include <raylib.h>

Scene::Scene(SceneId scene_id) : scene_id_(scene_id) {}

Scene::~Scene() {}

void Scene::Update() {}

void Scene::Draw() const {}

void Scene::OnEnter() { TraceLog(LOG_DEBUG, "Scene OnEnter"); }

void Scene::OnExit() { TraceLog(LOG_DEBUG, "Scene OnExit"); }
