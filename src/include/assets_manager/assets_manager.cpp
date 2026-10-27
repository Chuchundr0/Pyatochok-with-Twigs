#include "assets_manager.hpp"

std::unordered_map<std::string, Texture2D> AssetsManager::textures;
std::unordered_map<std::string, Texture2D> AssetsManager::atlas_assets;
Texture2D AssetsManager::atlas;

void AssetsManager::LoadAssets() {
	Image texture_image = {
		.data = TEXTURE_DATA,
		.width = TEXTURE_WIDTH,
		.height = TEXTURE_HEIGHT,
		.mipmaps = 1,
		.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
	};
	Texture2D texture_texture = LoadTextureFromImage(texture_image);
	Image player_image = {
        .data = PLAYER_DATA,
        .width = PLAYER_WIDTH,
        .height = PLAYER_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
	};
	Texture2D player_texture = LoadTextureFromImage(player_image);
	
	atlas_assets["texture"] = texture_texture;
	atlas_assets["player"] = player_texture;
}

void AssetsManager::LoadAtlas(const std::string &key) {
	atlas = atlas_assets[key];
};

void AssetsManager::LoadTextureFromAtlas(const std::string &key, const Rectangle &crop_rectangle) {
	Image atlas_image = LoadImageFromTexture(atlas);
	Image cropped_image = ImageFromImage(atlas_image, crop_rectangle);
	Texture2D cropped_texture = LoadTextureFromImage(cropped_image);
	UnloadImage(atlas_image);
	UnloadImage(cropped_image);

	textures[key] = cropped_texture;
}

Texture2D& AssetsManager::GetTexture(const std::string &key) {
	auto it = textures.find(key);
	if(it == textures.end()) {
		TraceLog(LOG_FATAL, "Texture not found: %s", key.c_str());	
		AssetsManager::UnloadAll();
		exit(1);
	}
	return it->second;
}

void AssetsManager::UnloadAll() {
	for(auto &[key, texture] : textures) {
		UnloadTexture(texture);
	}
	for(auto &[key, atlas_texture] : atlas_assets) {
		UnloadTexture(atlas_texture);
	}
	UnloadTexture(atlas);
	textures.clear();
}
