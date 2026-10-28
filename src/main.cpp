#include <vector>
#include <string>
#include <raylib.h>

#include "include/assets_manager/assets_manager.hpp"
#include "include/tilemap/tilemap.hpp"
#include "include/animation_manager/animation_manager.hpp"

#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 1920
#define HOLD_EXIT_TIME 1.5f

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pyatochok with twigs");
	SetExitKey(KEY_NULL);
	SetTargetFPS(120);

	AssetsManager::LoadAssets();
	Tilemap::GenerateMap();

	AssetsManager::LoadAtlas("player");
	AssetsManager::LoadTextureFromAtlas("player_idle_01", (Rectangle){0, 16, 16, 16});
	AssetsManager::LoadTextureFromAtlas("player_idle_02", (Rectangle){16, 16, 16, 16});
	AssetsManager::LoadTextureFromAtlas("player_idle_03", (Rectangle){32, 16, 16, 16});

	std::vector<Texture2D> animation_frames;
	animation_frames.push_back(AssetsManager::GetTexture("player_idle_01"));
	animation_frames.push_back(AssetsManager::GetTexture("player_idle_02"));
	animation_frames.push_back(AssetsManager::GetTexture("player_idle_03"));
	
	Animation player_animation(animation_frames, 15.0f);

	float pressedExitKeyTime = 0.0f;
	while(!WindowShouldClose()) {
		if(pressedExitKeyTime >= HOLD_EXIT_TIME) break;
		if(IsKeyDown(KEY_ESCAPE)) pressedExitKeyTime += GetFrameTime();
		else pressedExitKeyTime = 0.0f;
	
		player_animation.Update();

		BeginDrawing();

		ClearBackground(SKYBLUE);
		Tilemap::DrawMap();
		player_animation.DrawFrame((Vector2){0.0f, 0.0f}, 1);

		EndDrawing();
	}

	AssetsManager::UnloadAll();
	CloseWindow();
}
