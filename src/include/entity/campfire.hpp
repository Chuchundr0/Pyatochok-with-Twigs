#pragma once

#include <vector>
#include <raylib.h>

#include "entity.hpp"
#include "../animation/animation.hpp"
#include "../assets_manager/assets_manager.hpp"

#define CF_ANIMATIONS_LEVELS_Y 3
#define CF_ANIMATIONS_LEVELS_X 2
#define CF_ANIMATIONS_OFFSET_Y 1
#define CF_MIN_COMBUSTION 0.0f
#define CF_MAX_COMBUSTION 100.0f
#define CF_REDUCED_COMBUSTION 0.005f
#define CF_TEXTURE_SIZE 32
#define CF_TEXTURE_SCALE 4.0f

class Campfire : public Entity{
public:
	std::vector<Animation> animations;
	float combustion_level = CF_MAX_COMBUSTION;

	Campfire(const Vector2 &position);
	void LoadAnimations();
	void Update();
	void DrawAnimationFrame();
};
