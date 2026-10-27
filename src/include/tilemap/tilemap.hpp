#pragma once

#include <random>
#include <raylib.h>

#include "../assets_manager/assets_manager.hpp"

#define TILEMAP_HEIGHT 19
#define TILEMAP_WIDTH 30
#define TILEMAP_PLATFORM_HEIGHT 5
#define TILE_SIZE 64.0f
#define TILE_SCALE 4.0f

class Tile {
public:
	Rectangle collision;
	Texture2D texture;

	Tile() = default;
	Tile(const Rectangle &collision, Texture2D texture);
};

class Tilemap {
public: 
	static Tile tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH];
	
	static void GenerateMap();
	static void DrawMap();
};
