#pragma once

#include <vector>
#include <raylib.h>

class Animation {
public:
	std::vector<Texture2D> animation_frames;
	int current_frame = 0;
	float fps = 1.0f;
	float timer = 0.0f;

	Animation() = default;
	Animation(const std::vector<Texture2D> &animation_frames, float fps);
	void Update();
	void DrawFrame(const Vector2 &position, const int &direction);
};
