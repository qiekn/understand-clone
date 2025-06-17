#include "graphic.h"
#include <raylib.h>
#include <cmath>
#include "math.h"
#include "vector2int.h"

void graphic::DrawDottedLine(int x1, int y1, int x2, int y2, float interval, float length) {
  DrawDottedLine(x1, y1, x2, y2, interval, length, 1.0f, BLACK);
}

void graphic::DrawDottedLine(int x1, int y1, int x2, int y2, float interval, float length,
                             float thickness, Color color) {
  const float line_length = math::Vector2IntDistance({x1, y1}, {x2, y2});

  if (line_length <= 0.0f) return;

  const float dx = (x2 - x1) / line_length;
  const float dy = (y2 - y1) / line_length;
  const float cycle_length = length + interval;

  float current_distance = 0.0f;

  while (current_distance < line_length) {
    const float start_x = x1 + dx * current_distance;
    const float start_y = y1 + dy * current_distance;

    const float segment_end_distance = std::min(current_distance + length, line_length);
    const float end_x = x1 + dx * segment_end_distance;
    const float end_y = y1 + dy * segment_end_distance;

    if (thickness <= 1.0f) {
      DrawLine(static_cast<int>(std::round(start_x)), static_cast<int>(std::round(start_y)),
               static_cast<int>(std::round(end_x)), static_cast<int>(std::round(end_y)), color);
    } else {
      DrawLineEx({start_x, start_y}, {end_x, end_y}, thickness, color);
    }

    current_distance += cycle_length;
  }
}

void graphic::DrawDottedLineV(Vector2Int a, Vector2Int b, float interval, float length) {
  DrawDottedLineV(a, b, interval, length, 1.0f, BLACK);
}

void graphic::DrawDottedLineV(Vector2Int a, Vector2Int b, float interval, float length,
                              float thickness, Color color) {
  DrawDottedLine(a.x, a.y, b.x, b.y, interval, length, thickness, color);
}

void graphic::DrawLevelGrid(int x, int y, int w, int h, Color background = {145, 207, 145, 255},
                            Color border = {34, 159, 30, 255}) {
  DrawRectangle(x, y, w, h, background);
  float scale = 0.8;
  Rectangle rec = {x + w * 0.5f * (1 - scale), y + h * 0.5f * (1 - scale), w * scale, h * scale};
  DrawRectangleLinesEx(rec, 3, border);
}
