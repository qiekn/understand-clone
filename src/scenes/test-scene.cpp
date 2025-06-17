#include "test-scene.h"
#include <raylib.h>
#include "graphic.h"
#include "scene.h"

TestScene::TestScene() : Scene(SceneId::kTest) {}

TestScene::~TestScene() {}

void TestScene::Update() {}

void TestScene::Draw() const {
  BeginDrawing();
  ClearBackground(BLACK);
  graphic::DrawLevelGrid(100, 100, 100, 100, RED, BLUE);

  graphic::DrawDottedLine(200, 200, 500, 200, 10, 10, 3, RED);
  EndDrawing();
}

void TestScene::OnEnter() {}

void TestScene::OnExit() {}
