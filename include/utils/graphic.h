#pragma once

#include <raylib.h>
#include "vector2int.h"

// clang-format off
namespace graphic {
void DrawDottedLine(int x1, int y1, int x2, int y2, float interval, float length);
void DrawDottedLine(int x1, int y1, int x2, int y2, float interval, float length, float thickness, Color color);
void DrawDottedLineV(Vector2Int point1, Vector2Int point2, float interval, float length);
void DrawDottedLineV(Vector2Int a, Vector2Int b, float interval, float length, float thickness, Color color);

void DrawLevelGrid(int x, int y, int w, int h, Color background, Color border);
}  // namespace graphic
