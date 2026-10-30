#include "assets_manager.hpp"

std::vector<Texture2D> AssetsManager::textures_buffer;
std::unordered_map<std::string, Texture2D> AssetsManager::atlases_buffer;
Texture2D AssetsManager::current_atlas;

void AssetsManager::LoadAssets() {
	Image textures_image = {
		.data = TEXTURE_DATA,
		.width = TEXTURE_WIDTH,
		.height = TEXTURE_HEIGHT,
		.mipmaps = 1,
		.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
	};
	Texture2D textures_texture = LoadTextureFromImage(textures_image);
	Image player_image = {
        .data = PLAYER_DATA,
        .width = PLAYER_WIDTH,
        .height = PLAYER_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
	};
	Texture2D player_texture = LoadTextureFromImage(player_image);
	
	atlases_buffer["texture"] = textures_texture;
	atlases_buffer["player"] = player_texture;
}

void AssetsManager::LoadAtlas(const std::string &key) {
	current_atlas = atlases_buffer[key];
};

Texture2D& AssetsManager::LoadTextureFromAtlas(const Rectangle &crop_rectangle) {
	Image atlas_image = LoadImageFromTexture(current_atlas);
	Image cropped_image = ImageFromImage(atlas_image, crop_rectangle);
	Texture2D cropped_texture = LoadTextureFromImage(cropped_image);
	UnloadImage(atlas_image);
	UnloadImage(cropped_image);
	
	textures_buffer.push_back(cropped_texture);
	return textures_buffer.back();
}

void AssetsManager::UnloadAll() {
	for(auto &texture : textures_buffer) {
		UnloadTexture(texture);
	}
	for(auto &[key, atlas_texture] : atlases_buffer) {
		UnloadTexture(atlas_texture);
	}
	textures_buffer.clear();
}
