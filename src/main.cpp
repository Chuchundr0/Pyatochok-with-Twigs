#include <string>
#include <raylib.h>

#include "include/assets_manager/assets_manager.hpp"
#include "include/tilemap/tilemap.hpp"

#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 1920
#define HOLD_EXIT_TIME 1.5f

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pyatochok with twigs");
	SetExitKey(KEY_NULL);
	SetTargetFPS(120);

	AssetsManager::LoadAssets();
	Tilemap::GenerateMap();

	float pressedExitKeyTime = 0.0f;
	while(!WindowShouldClose()) {
		if(pressedExitKeyTime >= HOLD_EXIT_TIME) break;
		if(IsKeyDown(KEY_ESCAPE)) pressedExitKeyTime += GetFrameTime();
		else pressedExitKeyTime = 0.0f;
	
		BeginDrawing();

		ClearBackground(SKYBLUE);
		Tilemap::DrawMap();

		EndDrawing();
	}

	AssetsManager::UnloadAll();
	CloseWindow();
}
