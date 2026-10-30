#pragma once

#include <cmath>
#include <raylib.h>

#include "../assets_manager/assets_manager.hpp"
#include "../animation/animation.hpp"

#define GROUND_LEVEL_Y 848
#define MAX_SPEED_X 200.0f
#define MAX_SPEED_Y 400.0f
#define ACCEL_SPEED_X 10.0f
#define ANIMATIONS_LEVELS_Y 4
#define ANIMATIONS_LEVELS_X 3
#define PLAYER_TEXTURE_SIZE 16
#define GRAVITY 2000.0f
#define GRAVITY_HOLD 1000.0f

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
	Player(Vector2 position);
	void LoadAnimations();
	void Update();
	void DrawAnimationFrame();
};
