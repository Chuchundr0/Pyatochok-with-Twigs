#include "player.hpp"

Player::Player(Vector2 position) :
	position(position) {}

void Player::LoadAnimations() {
	AssetsManager::LoadAtlas("player");
	for(int y = 0; y < ANIMATIONS_LEVELS_Y; ++y) {
		std::vector<Texture2D> textures;
		textures.reserve(ANIMATIONS_LEVELS_X);
		for(int x = 0; x < ANIMATIONS_LEVELS_X; ++x) {
			Rectangle crop_rectangle = {(float)(PLAYER_TEXTURE_SIZE * x), (float)(PLAYER_TEXTURE_SIZE * y), PLAYER_TEXTURE_SIZE, PLAYER_TEXTURE_SIZE};
			textures.push_back(AssetsManager::LoadTextureFromAtlas(crop_rectangle));
		}
		Animation new_animation(textures, 0.5f);
		animations.push_back(new_animation);
	}
}

void Player::Update() {
	float delta_time = GetFrameTime();

	float target_speed = 0.0f;
	if(IsKeyDown(KEY_A)) {
		direction = 0;
		target_speed = -MAX_SPEED_X;
	}
	if(IsKeyDown(KEY_D)) {
		direction = 1;
		target_speed = MAX_SPEED_X;
	}

    float smoothing = 1.0f - std::exp(-ACCEL_SPEED_X * delta_time);
    speed_x += (target_speed - speed_x) * smoothing;
    position.x += speed_x * delta_time;

	if(IsKeyPressed(KEY_SPACE) && on_ground) {
		speed_y = -MAX_SPEED_Y;
		on_ground = false;
		is_jumping = true;
	}

    bool holding_up = IsKeyDown(KEY_SPACE) && speed_y < 0.0f && is_jumping;
    float gravity = holding_up ? GRAVITY_HOLD : GRAVITY;

    speed_y += gravity * delta_time;
    if (speed_y >  MAX_SPEED_Y) speed_y =  MAX_SPEED_Y;
    if (speed_y < -MAX_SPEED_Y) speed_y = -MAX_SPEED_Y;
    position.y += speed_y * delta_time;

    if (position.y >= GROUND_LEVEL_Y) {
        position.y  = GROUND_LEVEL_Y;
        speed_y     = 0.0f;
        on_ground   = true;
        is_jumping  = false;
    }
    if (IsKeyReleased(KEY_SPACE)) is_jumping = false;
}

void Player::DrawAnimationFrame() {
	if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
		if(hold_twigs) {
			animations[3].Update();
			animations[3].DrawFrame(position, direction);
		}
		else if(!hold_twigs) {
			animations[1].Update();
			animations[1].DrawFrame(position, direction);
		}
	}
	else {
		if(hold_twigs) {
			animations[2].Update();
			animations[2].DrawFrame(position, direction);
		}
		else if(!hold_twigs) {
			animations[0].Update();
			animations[0].DrawFrame(position, direction);
		}		
	}
}
