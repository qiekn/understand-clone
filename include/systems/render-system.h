#pragma once

#include <vector>
#include "node.h"
#include "utils/class-util.h"

class RenderSystem {
  MAKE_SINGLETON(RenderSystem);

public:
  void Update();
  void Draw() const;

private:
  RenderSystem();

public:
  std::vector<Node> nodes;
};
