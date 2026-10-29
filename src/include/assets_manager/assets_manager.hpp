#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <raylib.h>

#include "../assets/textures.hpp"
#include "../assets/player.hpp"

class AssetsManager {
private:	
	static std::vector<Texture2D> textures_buffer;
	static std::unordered_map<std::string, Texture2D> atlases_buffer;
	static Texture2D current_atlas;

public:
	static void LoadAssets();
	static void LoadAtlas(const std::string &key);
	static Texture2D& LoadTextureFromAtlas(const Rectangle &crop_rectangle);
	static void UnloadAll();
};
