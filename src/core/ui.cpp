#include "ui.h"

UI::UI() {
  top_right_btns_.emplace_back(Rectangle(0, 0, 100, 100), RED, "btn1");
  top_right_btns_.emplace_back(Rectangle(100, 0, 100, 100), GREEN, "btn2");
  top_right_btns_.emplace_back(Rectangle(200, 0, 100, 100), BLUE, "btn3");
}

UI::~UI() {}

void UI::Update() {
  Vector2 mouse_pos = GetMousePosition();
  for (auto& btn : top_right_btns_) {
    btn.Update(mouse_pos);
  }
}

void UI::Draw() const { DrawTopRightButtons(); }

void UI::DrawTopRightButtons() const {
  for (const auto& btn : top_right_btns_) {
    btn.Draw();
  }
}
