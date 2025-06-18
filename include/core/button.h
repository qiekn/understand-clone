#pragma once

#include <raylib.h>
#include <functional>
#include <string>

class Button {
public:
  enum class State {
    kNormal,
    kHover,
    kClicked,
  };

  Button(Rectangle rec, Color color, std::string text);
  virtual ~Button();

  void Update(Vector2 mouse_pos);
  void Draw() const;

  bool IsHover() const { return state_ == State::kHover; }

  void SetBounds(Rectangle rec) { bounds_ = rec; }
  void SetCallbackFunction(std::function<void()> callback) { callback_ = callback; }

private:
  State state_ = Button::State::kNormal;
  Rectangle bounds_;
  Texture2D texture_;
  Rectangle source_rec_;
  Sound click_sound_;

  bool has_texture_;
  bool has_sound_;

  std::string text_;
  Color color_;
  Color background_color_ = GREEN;
  std::function<void()> callback_;
};
