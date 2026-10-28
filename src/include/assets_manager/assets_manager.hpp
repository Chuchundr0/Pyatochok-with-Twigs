#pragma once

#include <unordered_map>
#include <string>
#include <raylib.h>

#include "../assets/texture.hpp"
#include "../assets/player.hpp"

class AssetsManager {
private:	
	static std::unordered_map<std::string, Texture2D> textures;
	static std::unordered_map<std::string, Texture2D> atlas_assets;
	static Texture2D atlas;

public:
	static void LoadAssets();
	static void LoadAtlas(const std::string &key);
	static void LoadTextureFromAtlas(const std::string &key, const Rectangle &crop_rectangle);
	static Texture2D& GetTexture(const std::string &key);
	static void UnloadAll();
};
