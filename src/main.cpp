#include <raylib.h>
#include <memory>
#include "font.h"
#include "menu-scene.h"
#include "scene-manager.h"
#include "scene.h"
#include "systems/render-system.h"
#include "test-scene.h"
#include "utils/class-util.h"

int main() {
  const int kScreenWidth = 1024;
  const int kScreenHeight = 768;

  InitWindow(kScreenWidth, kScreenHeight, "game");
  SetTargetFPS(144);
  SetTraceLogLevel(LOG_DEBUG);
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  LoadGlobalFonts();
  InitAudioDevice();
  CONSTRUCT_SINGLETON(RenderSystem);

  SceneManager scene_manager;
  scene_manager.Add(SceneId::kMenu, std::make_unique<MenuScene>());
  scene_manager.Add(SceneId::kTest, std::make_unique<TestScene>());
  scene_manager.Switch(SceneId::kTest);

  bool is_test = true;

  while (!WindowShouldClose()) {
    /* update */
    scene_manager.Update();

    /* draw */
    scene_manager.Draw();

    if (IsKeyPressed(KEY_TAB)) {
      if (!is_test)
        scene_manager.Switch(SceneId::kTest);
      else
        scene_manager.Switch(SceneId::kMenu);
      is_test = !is_test;
    }
  }

  CloseWindow();
  CloseAudioDevice();
  return 0;
}
