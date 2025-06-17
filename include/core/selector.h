#pragma once

#include <raylib.h>
#include "node.h"

class Selector : public Node {
public:
  Selector();
  virtual ~Selector();

  void Move(int dx, int dy);
  void MoveTo(int x, int y);
  void Focus();
  void Update() override;
  void Draw() const override;

  void SetColor(Color color);

private:
  int x_ = 0;
  int y_ = 0;
  Color color_ = YELLOW;
};
