#pragma once

#include <vector>
#include "button.h"
class UI {
public:
  UI();
  virtual ~UI();

  void Update();
  void Draw() const;

private:
  void DrawTopRightButtons() const;
  std::vector<Button> top_right_btns_;
};
