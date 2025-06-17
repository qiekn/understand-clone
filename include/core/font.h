#pragma once

#include <raylib.h>

extern Font noto_regular;
extern Font noto_italic;

namespace custom_font {
const float spacing = 0;
}

/**
 * @brief use this after raylib init window function
 */
void LoadGlobalFonts();

void DrawMyText();
