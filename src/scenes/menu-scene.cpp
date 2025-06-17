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
  const float scale_x = static_cast<float>(GetScreenWidth()) / (kMapWidth * kGridSize);
  const float scale_y = static_cast<float>(GetScreenHeight()) / (kMapHeight * kGridSize);
  const float scale = std::min(scale_x, scale_y) * 0.8f;  // 留一些边距

  // 计算偏移量以居中显示
  const float offset_x = (GetScreenWidth() - kMapWidth * kGridSize * scale) / 2.0f;
  const float offset_y = (GetScreenHeight() - kMapHeight * kGridSize * scale) / 2.0f;
  DrawRectangle(offset_x, offset_y, kMapWidth * kGridSize, kMapHeight * kGridSize, RED);

  // 统一的边框厚度
  const int border_thickness = 1;

  // 绘制所有已解锁的关卡
  for (const auto& [id, level] : levels_) {
    if (!level.unlocked) continue;

    // 计算关卡位置和大小
    const float x = offset_x + level.x * kGridSize * scale;
    const float y = offset_y + level.y * kGridSize * scale;
    const float size = kGridSize * scale;

    // 确定关卡颜色
    Color level_color = GREEN;
    if (level.completed) {
      level_color = PINK;
    }
    if (level.x == selected_x_ && level.y == selected_y_) {
      level_color = YELLOW;  // 选中的关卡
    }

    // 绘制关卡背景（留出边框空间）
    const float inner_x = x + border_thickness;
    const float inner_y = y + border_thickness;
    const float inner_size = size - 2 * border_thickness;

    DrawRectangle(static_cast<int>(inner_x), static_cast<int>(inner_y),
                  static_cast<int>(inner_size), static_cast<int>(inner_size), level_color);

    // 绘制统一厚度的边框
    DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(size),
                       static_cast<int>(size), BLACK);

    // 绘制关卡ID（精确居中）
    const int font_size = std::max(12, static_cast<int>(32 * scale));
    const Vector2 text_size =
        MeasureTextEx(noto_regular, level.id.c_str(), static_cast<float>(font_size), 1.0f);

    // 在内部区域居中
    const float text_x = inner_x + (inner_size - text_size.x) / 2.0f;
    const float text_y = inner_y + (inner_size - text_size.y) / 2.0f;

    DrawTextEx(noto_regular, level.id.c_str(), Vector2(text_x, text_y),
               static_cast<float>(font_size), 1.0f, BLACK);

    // 绘制完成标记（优化位置和大小）
    if (level.completed) {
      const int check_size = std::max(10, static_cast<int>(16 * scale));
      const float check_x = inner_x + inner_size - check_size - 2;
      const float check_y = inner_y + 2;

      // 绘制白色背景圆圈使标记更清晰
      DrawCircle(static_cast<int>(check_x + check_size / 2.0f),
                 static_cast<int>(check_y + check_size / 2.0f), check_size / 2.0f + 2, WHITE);
      DrawCircleLines(static_cast<int>(check_x + check_size / 2.0f),
                      static_cast<int>(check_y + check_size / 2.0f), check_size / 2.0f + 2,
                      DARKGREEN);

      DrawText("✓", static_cast<int>(check_x), static_cast<int>(check_y), check_size, DARKGREEN);
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
