#pragma once
#include"Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1;
	int speed = 3;

	
	TransformComponent()
	{
		position.Zero();

	}
	TransformComponent(float sc)
	{
		//position.Zero();
		//placing the player in the desired place 
		position.x = 100;
		position.y = 100;
		scale = sc;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y,int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{

		//not updating players position instead scrolling the background
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};
