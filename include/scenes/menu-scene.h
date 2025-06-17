#pragma once

#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include "scene.h"
#include "selector.h"

struct Level {
  int x, y;
  std::string id;
  bool completed;
  bool unlocked;
  std::vector<std::string> adjacent_levels;
};

class MenuScene : public Scene {
public:
  /* method */
  MenuScene();
  virtual ~MenuScene();

  void Update() override;
  void Draw() const override;
  void OnEnter() override;
  void OnExit() override;

private:
  void DrawFitToScreenMode() const;
  void DrawFixedSizeMode() const;
  void DrawUI() const;

  void HandleInput();
  void UpdateCamera();

  void ToggleCurrentLevelCompletion();

  void InitLevels();

public:
  /* field */
  static constexpr int kGridSize = 80;
  static constexpr int kMapWidth = 10;
  static constexpr int kMapHeight = 8;

  enum class ZoomMode { kFitToScreen, kFixedSize };

private:
  std::map<std::string, Level> levels_;
  std::vector<std::vector<std::string>> grids_;

  Selector selector_;
  int selected_x_, selected_y_;
  ZoomMode current_zoom_mode_ = ZoomMode::kFitToScreen;
  Camera2D camera_;
};
