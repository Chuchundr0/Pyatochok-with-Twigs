#include "tilemap.hpp"

Tile Tilemap::tilemap[TILEMAP_HEIGHT][TILEMAP_WIDTH];

Tile::Tile(const Rectangle &collision, Texture2D texture) :
	collision(collision), texture(texture) {};

void Tilemap::GenerateMap() {
	AssetsManager::LoadAtlas("texture");
	Texture2D dirt_texture_01 = AssetsManager::LoadTextureFromAtlas((Rectangle){112, 112, 16, 16});
	Texture2D dirt_texture_02 = AssetsManager::LoadTextureFromAtlas((Rectangle){96, 112, 16, 16});
	Texture2D grass_texture_01 = AssetsManager::LoadTextureFromAtlas((Rectangle){96, 96, 16, 16});
	Texture2D grass_texture_02 = AssetsManager::LoadTextureFromAtlas((Rectangle){112, 96, 16, 16});
	
	std::random_device randomizer;
	std::mt19937 generator(randomizer());
	std::uniform_int_distribution<int> dist(1, 100);

	for(int y = TILEMAP_HEIGHT - TILEMAP_PLATFORM_HEIGHT; y < TILEMAP_HEIGHT; ++y) {
		for(int x = 0; x < TILEMAP_WIDTH; ++x) {
			int randomize_texture = dist(generator);
			if(y == TILEMAP_HEIGHT - TILEMAP_PLATFORM_HEIGHT) {
				if(randomize_texture % 2 == 0) {
					tilemap[y][x] = Tile((Rectangle){(float)(x * TILE_SIZE), (float)(y * TILE_SIZE), TILE_SIZE, TILE_SIZE}, grass_texture_01);
				}
				else {
					tilemap[y][x] = Tile((Rectangle){(float)(x * TILE_SIZE), (float)(y * TILE_SIZE), TILE_SIZE, TILE_SIZE}, grass_texture_02);
				}
			}
			else {
				if(randomize_texture % 2 == 0) {
					tilemap[y][x] = Tile((Rectangle){(float)(x * TILE_SIZE), (float)(y * TILE_SIZE), TILE_SIZE, TILE_SIZE}, dirt_texture_01);
				}
				else {
					tilemap[y][x] = Tile((Rectangle){(float)(x * TILE_SIZE), (float)(y * TILE_SIZE), TILE_SIZE, TILE_SIZE}, dirt_texture_02);
				}
			}
		}
	}
}

void Tilemap::DrawMap() {
	for(int y = 0; y < TILEMAP_HEIGHT; ++y) {
		for(int x = 0; x < TILEMAP_WIDTH; ++x) {
			DrawTextureEx(tilemap[y][x].texture, (Vector2){(float)(x * TILE_SIZE), (float)(y * TILE_SIZE)}, 0.0f, TILE_SCALE, WHITE);
		}
	}
}
