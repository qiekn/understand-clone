#include "render-system.h"

void RenderSystem::Update() {
  for (auto& node : nodes) {
    node.Update();
  }
}

void RenderSystem::Draw() const {
  for (const auto& node : nodes) {
    node.Draw();
  }
}

RenderSystem::RenderSystem() {}
