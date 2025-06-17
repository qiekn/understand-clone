#pragma once

#include <raylib.h>
#include "scene.h"
#include "selector.h"

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

public:
  /* field */
  static constexpr int kGridSize = 80;
  static constexpr int kMapWidth = 10;
  static constexpr int kMapHeight = 8;

  enum class ZoomMode { kFitToScreen, kFixedSize };

private:
  Selector selector_;
  ZoomMode current_zoom_mode_ = ZoomMode::kFitToScreen;
  Camera2D camera_;
};
