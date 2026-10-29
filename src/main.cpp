#include <vector>
#include <string>
#include <raylib.h>

#include "include/assets_manager/assets_manager.hpp"
#include "include/tilemap/tilemap.hpp"
#include "include/animation/animation.hpp"

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
	
	std::vector<Texture2D> textures_player;
	textures_player.push_back(AssetsManager::LoadTextureFromAtlas((Rectangle){0, 0, 16, 16}));
	textures_player.push_back(AssetsManager::LoadTextureFromAtlas((Rectangle){16, 0, 16, 16}));
	textures_player.push_back(AssetsManager::LoadTextureFromAtlas((Rectangle){32, 0, 16, 16}));

	Animation player_animation(textures_player, 0.3f);

	float pressedExitKeyTime = 0.0f;
	while(!WindowShouldClose()) {
		if(pressedExitKeyTime >= HOLD_EXIT_TIME) break;
		if(IsKeyDown(KEY_ESCAPE)) pressedExitKeyTime += GetFrameTime();
		else pressedExitKeyTime = 0.0f;
	
		player_animation.Update();

		BeginDrawing();

		ClearBackground((Color){156, 192, 255, 255});
		Tilemap::DrawMap();

		player_animation.DrawFrame((Vector2){0, 0}, 0);

		EndDrawing();
	}

	AssetsManager::UnloadAll();
	CloseWindow();
}
