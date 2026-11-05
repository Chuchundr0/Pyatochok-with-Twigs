#include "animation.hpp"

Animation::Animation(const std::vector<Texture2D> &textures, float frame_time) :
	textures(textures), frame_time(frame_time) {}

void Animation::Update() {
	animation_timer += GetFrameTime();
	if(animation_timer >= frame_time) {
		animation_timer -= frame_time;
		current_frame = (current_frame + 1) % (int)textures.size();
	}
}

void Animation::DrawFrame(const Vector2 &position, short direction) {
	Rectangle source = {0.0f, 0.0f, (float)textures[current_frame].width, (float)textures[current_frame].height};
	if(direction == 0) {
		source = {0.0f, 0.0f, (float)-textures[current_frame].width, (float)textures[current_frame].height};
	}
	Rectangle dest = {position.x, position.y, (float)textures[current_frame].width * ANIMATION_TEXTURE_SCALE, (float)textures[current_frame].height * ANIMATION_TEXTURE_SCALE};
	DrawTexturePro(textures[current_frame], source, dest, {0, 0}, 0.0f, WHITE);
}

void Animation::SetAnimationTimer(float animation_timer) {
	this->animation_timer = animation_timer;
}
