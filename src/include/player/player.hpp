#pragma once

#include <cmath>
#include <raylib.h>

#include "../assets_manager/assets_manager.hpp"
#include "../animation/animation.hpp"

#define PL_GROUND_LEVEL 840
#define PL_MAX_SPEED_X 250.0f
#define PL_MAX_SPEED_Y 550.0f
#define PL_ACCEL_SPEED_X 15.0f
#define PL_ANIMATIONS_LEVELS_Y 6
#define PL_ANIMATIONS_LEVELS_X 3
#define PL_TEXTURE_SIZE 16
#define PL_GRAVITY 2300.0f
#define PL_GRAVITY_HOLD 1600.0f

class Player {
private:
	std::vector<Animation> animations;
	Vector2 position;
	float speed_y = 0.0f;
	float speed_x = 0.0f;
	short direction = 0;
	bool on_ground = false;
	bool is_jumping = false;
	bool hold_twigs = false;

public:
	Player(const Vector2 &position);
	void LoadAnimations();
	void Update();
	void DrawAnimationFrame();
};
