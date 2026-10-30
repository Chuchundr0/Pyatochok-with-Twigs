#pragma once

#include <vector>
#include <raylib.h>

#define TEXTURE_SIZE 64.0f

class Animation {
private:
	std::vector<Texture2D> textures;
	int current_frame = 0;
	float animation_timer = 0.0f;
	float frame_time = 1.0f;

public:
	Animation(std::vector<Texture2D> textures, const float &frame_time);
	void Update();
	void DrawFrame(const Vector2 &position, short direction);
	void SetAnimationTimer(const float &animation_timer);
};
