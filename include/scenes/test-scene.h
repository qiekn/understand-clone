#pragma once

#include "scene.h"
class TestScene : public Scene {
public:
  TestScene();
  virtual ~TestScene();

private:
  void Update() override;
  void Draw() const override;
  void OnEnter() override;
  void OnExit() override;
};
