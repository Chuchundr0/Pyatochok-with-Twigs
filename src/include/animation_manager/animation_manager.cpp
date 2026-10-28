#include "animation_manager.hpp"

Animation::Animation(const std::vector<Texture2D> &animation_frames, float fps) :
	animation_frames(animation_frames), fps(fps) {};

void Animation::Update() {
	timer += GetFrameTime();
	const float frame_time = 1.0f / fps;
	if(timer >= frame_time) {
		timer -= frame_time;
		current_frame = (current_frame + 1) % (int)animation_frames.size();
	}
}

void Animation::DrawFrame(const Vector2 &position, const int &direction) {
	Rectangle source;
	if(direction == 0) {
		source = {0, 0, animation_frames[current_frame].width, animation_frames[current_frame].height};
	}
	else {
		source = {0, 0, -animation_frames[current_frame].width, animation_frames[current_frame].height};
	}
	Rectangle dest = {position.x, position.y, animation_frames[current_frame].width * 4.0f, animation_frames[current_frame].height * 4.0f};
	DrawTexturePro(animation_frames[current_frame], source, dest, {0, 0}, 0.0f, WHITE);		
}
