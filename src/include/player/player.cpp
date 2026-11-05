#include "player.hpp"

Player::Player(const Vector2 &position) :
	position(position) {}

void Player::LoadAnimations() {
	AssetsManager::LoadAtlas("player");
	for(int y = 0; y < PL_ANIMATIONS_LEVELS_Y; ++y) {
		std::vector<Texture2D> textures;
		textures.reserve(PL_ANIMATIONS_LEVELS_X);
		for(int x = 0; x < PL_ANIMATIONS_LEVELS_X; ++x) {
			Rectangle crop_rectangle = {(float)(PL_TEXTURE_SIZE * x), (float)(PL_TEXTURE_SIZE * y), PL_TEXTURE_SIZE, PL_TEXTURE_SIZE};
			textures.push_back(AssetsManager::LoadTextureFromAtlas(crop_rectangle));
		}
		Animation new_animation(textures, 0.4f);
		animations.push_back(new_animation);
	}
}

void Player::Update() {
	float delta_time = GetFrameTime();

	float target_speed = 0.0f;
	if(IsKeyDown(KEY_A)) {
		direction = 0;
		target_speed = -PL_MAX_SPEED_X;
	}
	if(IsKeyDown(KEY_D)) {
		direction = 1;
		target_speed = PL_MAX_SPEED_X;
	}

    float smoothing = 1.0f - std::exp(-PL_ACCEL_SPEED_X * delta_time);
    speed_x += (target_speed - speed_x) * smoothing;
    position.x += speed_x * delta_time;

	if(IsKeyPressed(KEY_SPACE) && on_ground) {
		speed_y = -PL_MAX_SPEED_Y;
		on_ground = false;
		is_jumping = true;
	}

    bool holding_up = IsKeyDown(KEY_SPACE) && speed_y < 0.0f && is_jumping;
    float gravity = holding_up ? PL_GRAVITY_HOLD : PL_GRAVITY;

    speed_y += gravity * delta_time;
    if(speed_y > PL_MAX_SPEED_Y) speed_y = PL_MAX_SPEED_Y;
    if(speed_y < -PL_MAX_SPEED_Y) speed_y = -PL_MAX_SPEED_Y;
    position.y += speed_y * delta_time;

    if(position.y >= PL_GROUND_LEVEL) {
        position.y = PL_GROUND_LEVEL;
        speed_y = 0.0f;
        on_ground = true;
        is_jumping = false;
    }
    if(IsKeyReleased(KEY_SPACE)) is_jumping = false;
}

void Player::DrawAnimationFrame() {
	if(!hold_twigs) {
		if(!on_ground) {
			animations[2].Update();
			animations[2].DrawFrame(position, direction);
		}
		else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
			animations[1].Update();
			animations[1].DrawFrame(position, direction);
		}
		else {
			animations[0].Update();
			animations[0].DrawFrame(position, direction);
		}
	}
	else {
		if(!on_ground) {
			animations[5].Update();
			animations[5].DrawFrame(position, direction);
		}
		else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
			animations[4].Update();
			animations[4].DrawFrame(position, direction);
		}
		else {
			animations[3].Update();
			animations[3].DrawFrame(position, direction);
		}
	}
}
