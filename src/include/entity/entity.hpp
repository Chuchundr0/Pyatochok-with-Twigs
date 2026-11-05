#pragma once

#include <raylib.h>

class Entity {
public:
	Vector2 position;
	Texture2D texture;

	Entity(const Vector2 &position) : position(position) {}
};
