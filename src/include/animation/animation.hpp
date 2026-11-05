#pragma once

#include <vector>
#include <raylib.h>

#define ANIMATION_TEXTURE_SCALE 4.0f

class Animation {
private:
	std::vector<Texture2D> textures;
	int current_frame = 0;
	float animation_timer = 0.0f;
	float frame_time = 1.0f;

public:
	Animation(const std::vector<Texture2D> &textures, float frame_time);
	void Update();
	void DrawFrame(const Vector2 &position, short direction);
};
