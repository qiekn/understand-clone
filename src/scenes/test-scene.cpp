#include "test-scene.h"
#include <raylib.h>
#include <cstdint>
#include "scene.h"

TestScene::TestScene() : Scene(SceneId::kTest) {}

TestScene::~TestScene() {}

void TestScene::Update() { ui_.Update(); }

void TestScene::Draw() const {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  ui_.Draw();
  EndDrawing();
}

void TestScene::OnEnter() {}

void TestScene::OnExit() {}
