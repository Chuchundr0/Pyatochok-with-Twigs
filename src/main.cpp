#include <vector>
#include <string>
#include <raylib.h>

#include "include/assets_manager/assets_manager.hpp"
#include "include/tilemap/tilemap.hpp"
#include "include/animation/animation.hpp"
#include "include/player/player.hpp"

#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 1920
#define HOLD_EXIT_TIME 1.5f

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pyatochok with twigs");
	SetExitKey(KEY_NULL);
	SetTargetFPS(120);

	AssetsManager::LoadAssets();
	Tilemap::GenerateMap();

	Player player((Vector2){(float)WINDOW_WIDTH / 2.0f, 0.0f});
	player.LoadAnimations();

	float pressedExitKeyTime = 0.0f;
	while(!WindowShouldClose()) {
		if(pressedExitKeyTime >= HOLD_EXIT_TIME) break;
		if(IsKeyDown(KEY_ESCAPE)) pressedExitKeyTime += GetFrameTime();
		else pressedExitKeyTime = 0.0f;

		player.Update();

		BeginDrawing();

		ClearBackground((Color){156, 192, 255, 255});
		Tilemap::DrawMap();

		player.DrawAnimationFrame();

		EndDrawing();
	}

	AssetsManager::UnloadAll();
	CloseWindow();
}
