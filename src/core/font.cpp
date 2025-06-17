#include "font.h"
#include <raylib.h>

Font noto_regular;
Font noto_italic;

void LoadGlobalFonts() {
  noto_regular = LoadFont("assets/fonts/noto-regular.ttf");
  noto_italic = LoadFont("assets/fonts/noto-italic.ttf");
}

void DrawMyText(Font font, const char *text, int x, int y, float font_size,
                Color color) {
  Vector2 pos = Vector2{(float)x, (float)y};
  DrawTextEx(font, text, pos, font_size, custom_font::spacing, color);
}
