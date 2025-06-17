#include "menu-scene.h"
#include <raylib.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "font.h"
#include "nlohmann/json.hpp"
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

void MenuScene::OnEnter() { InitLevels(); }

void MenuScene::OnExit() {}

void MenuScene::DrawFitToScreenMode() const {
  // 计算缩放比例以适应整个地图
  // clang-format off
  float scale_x = static_cast<float>(GetScreenWidth()) / (kMapWidth * kGridSize);
  float scale_y = static_cast<float>(GetScreenHeight()) / (kMapHeight * kGridSize);
  float scale = std::min(scale_x, scale_y) * 0.8f;  // 留一些边距
  // clang-format on

  // 计算偏移量以居中显示
  float offset_x = (GetScreenWidth() - kMapWidth * kGridSize * scale) / 2.0f;
  float offset_y = (GetScreenHeight() - kMapHeight * kGridSize * scale) / 2.0f;

  // 绘制所有已解锁的关卡
  for (const auto& [id, level] : levels_) {
    if (!level.unlocked) continue;

    float x = offset_x + level.x * kGridSize * scale;
    float y = offset_y + level.y * kGridSize * scale;
    float size = kGridSize * scale;

    // 绘制关卡格子
    Color level_color = level.completed ? GREEN : LIGHTGRAY;
    if (level.x == selected_x_ && level.y == selected_y_) {
      level_color = YELLOW;  // 选中的关卡
    }

    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(size),
                  static_cast<int>(size), level_color);
    DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(size),
                       static_cast<int>(size), BLACK);

    // 绘制关卡ID
    // int font_size = static_cast<int>(32 * scale);
    int font_size = 32;
    Vector2 text_size =
        MeasureTextEx(GetFontDefault(), level.id.c_str(), static_cast<float>(font_size), 1.0f);
    float text_x = x + (size - text_size.x) / 2.0f;
    float text_y = y + (size - text_size.y) / 2.0f;
    DrawTextEx(noto_regular, level.id.c_str(), Vector2(text_x, text_y), font_size, 0, BLACK);

    // 绘制完成标记
    if (level.completed) {
      DrawText("✓", static_cast<int>(x + size * 0.8f), static_cast<int>(y + size * 0.8f),
               static_cast<int>(16 * scale), DARKGREEN);
    }
  }
}

void MenuScene::DrawFixedSizeMode() const {}

void MenuScene::DrawUI() const {
  // 绘制控制说明
  const char* intro_text = "wasd: move | space: toggle completion | z: toggle zoom mode | f5: save";
  DrawTextEx(noto_italic, intro_text, (Vector2){10, 10}, 32, 1, BLACK);

  // 绘制当前模式
  const char* mode_text =
      (current_zoom_mode_ == ZoomMode::kFitToScreen) ? "Mode: Fit to Screen" : "Mode: Fixed Size";
  DrawTextEx(noto_italic, mode_text, (Vector2){10, 40}, 32, 1, PINK);
}

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
    current_zoom_mode_ = (current_zoom_mode_ == ZoomMode::kFitToScreen) ? ZoomMode::kFixedSize
                                                                        : ZoomMode::kFitToScreen;
  }
}

void MenuScene::ToggleCurrentLevelCompletion() {}

void MenuScene::InitLevels() {
  grids_.resize(kMapHeight, std::vector<std::string>(kMapWidth, ""));
  try {
    std::ifstream file("data/map.json");
    if (!file.is_open()) {
      std::cerr << "Warning: Cannot open levels.json, using default layout" << std::endl;
      return;
    }

    nlohmann::json level_json;
    file >> level_json;
    file.close();

    if (level_json.contains("levels") && level_json["levels"]["grids"].is_array()) {
      for (const auto& grid : level_json["levels"]["grids"]) {
        Level level;
        level.x = grid["x"];
        level.y = grid["y"];
        TraceLog(LOG_DEBUG, "read json level: %d %d", level.x, level.y);
        level.id = grid["id"];
        level.completed = grid.value("completed", false);
        // level.unlocked = grid.value("unlocked", false);
        level.unlocked = true;

        levels_[level.id] = level;
        if (level.y >= grid.size() || (grids_.size() > 0 && level.x >= grids_[0].size())) {
          TraceLog(LOG_ERROR, "level %d %d out of range", level.x, level.y);
          continue;
        }
        grids_[level.y][level.x] = level.id;
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Error loading levels.json: " << e.what() << std::endl;
  }
}
