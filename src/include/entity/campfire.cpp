#include "campfire.hpp"

Campfire::Campfire(const Vector2 &position) : 
	Entity(position) {}

void Campfire::LoadAnimations() {
	AssetsManager::LoadAtlas("texture");
	Rectangle crop_rectangle = {32, 0, CF_TEXTURE_SIZE, CF_TEXTURE_SIZE};
	texture = AssetsManager::LoadTextureFromAtlas(crop_rectangle);
	
	for(int y = CF_ANIMATIONS_OFFSET_Y; y < CF_ANIMATIONS_LEVELS_Y + CF_ANIMATIONS_OFFSET_Y; ++y) {
		std::vector<Texture2D> textures;
		textures.reserve(CF_ANIMATIONS_LEVELS_X);
		for(int x = 0; x < CF_ANIMATIONS_LEVELS_X; ++x) {
			Rectangle crop_rectangle = {(float)(CF_TEXTURE_SIZE * x), (float)(CF_TEXTURE_SIZE * y), CF_TEXTURE_SIZE, CF_TEXTURE_SIZE};
			textures.push_back(AssetsManager::LoadTextureFromAtlas(crop_rectangle));
		}
		Animation new_animation(textures, 0.2f);
		animations.push_back(new_animation);
	}
}

void Campfire::Update() {
	if(combustion_level > CF_MIN_COMBUSTION) {
		combustion_level -= CF_REDUCED_COMBUSTION;
	}
}

void Campfire::DrawAnimationFrame() {
	if(combustion_level >= 70.0f) {
		animations[2].Update();
		animations[2].DrawFrame(position, 0);
	}
	else if(combustion_level >= 40.0f) {
		animations[1].Update();
		animations[1].DrawFrame(position, 0);
	}
	else if(combustion_level >= 1.0f) {
		animations[0].Update();
		animations[0].DrawFrame(position, 0);
	}
	else {
		Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
		Rectangle dest = {position.x, position.y, (float)texture.width * CF_TEXTURE_SCALE, (float)texture.height * CF_TEXTURE_SCALE};
		DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, WHITE);
	}
}
