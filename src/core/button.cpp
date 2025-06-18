#include "button.h"
#include <raylib.h>

Button::Button(Rectangle rec, Color color, std::string text)
    : bounds_(rec), background_color_(color), text_(text) {
  callback_ = [this]() { TraceLog(LOG_DEBUG, "Button \'%s' clicked!", text_.c_str()); };
}

Button::~Button() {}

void Button::Update(Vector2 mouse_pos) {
  if (CheckCollisionPointRec(mouse_pos, bounds_)) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      state_ = State::kClicked;
    } else {
      state_ = State::kHover;
    }
  } else {
    state_ = State::kNormal;
  }

  switch (state_) {
    case State::kHover:
      color_ = PINK;
      break;
    case State::kClicked:
      color_ = BROWN;
      if (callback_) {
        callback_();
      }
      break;
    case State::kNormal:
      color_ = background_color_;
      break;
    default:
      break;
  }
}

void Button::Draw() const { DrawRectanglePro(bounds_, {0.5f, 0.5f}, 0, color_); }
