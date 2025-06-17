#include "menu-scene.h"
#include <raylib.h>
#include "scene.h"

MenuScene::MenuScene() : Scene(SceneId::kMenu) {}

MenuScene::~MenuScene() {}

void MenuScene::Update() {
  HandleInput();
  UpdateCamera();
}

void MenuScene::Draw() const {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (current_zoom_mode_ == ZoomMode::kFitToScreen) {
    DrawFitToScreenMode();
  } else {
    BeginMode2D(camera_);
    DrawFixedSizeMode();
    EndMode2D();
  }

  DrawUI();
  EndDrawing();
}

void MenuScene::OnEnter() {}

void MenuScene::OnExit() {}

void MenuScene::DrawFitToScreenMode() const {}

void MenuScene::DrawFixedSizeMode() const {}

void MenuScene::DrawUI() const {}

void MenuScene::UpdateCamera() {}

void MenuScene::HandleInput() {
  if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
    selector_.Move(0, -1);
  }
  if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
    selector_.Move(0, 1);
  }
  if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
    selector_.Move(-1, 0);
  }
  if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
    selector_.Move(1, 0);
  }

  if (IsKeyPressed(KEY_SPACE)) {
    ToggleCurrentLevelCompletion();
  }

  if (IsKeyPressed(KEY_Z)) {
    current_zoom_mode_ = (current_zoom_mode_ == ZoomMode::kFitToScreen)
                             ? ZoomMode::kFixedSize
                             : ZoomMode::kFitToScreen;
  }
}

void MenuScene::ToggleCurrentLevelCompletion() {}
