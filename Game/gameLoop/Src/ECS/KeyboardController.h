#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "../Collision.h"
#include "../Map.h"

class KeyboardComtroller : public Component
{
public:
	int ballPosition = 0;
	int tempXBall, tempYBall;
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (Collision::hitCount < 3)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_KP_ENTER:
					Map::startMapMovement = true;
					break;
				case SDLK_h:
					if (Map::startMapMovement == true && Game::updateCounter<=1500)// && mapReachedZero==true
					{
						Game::ballMoving = true;
						if (transform->velocity.x == 0 && transform->velocity.y == 0)
						{
							tempXBall = transform->position.x;
							tempYBall = transform->position.y;
						}
						transform->velocity.y = 1;
						transform->velocity.x = 1;
					}
					break;
				case SDLK_SPACE:
				{
					if (Map::startMapMovement == true && Game::ballMoving == false && Game::updateCounter<=1500)//player can aim the ball even when map has not started 
					{
						ballPosition++;
						if (ballPosition % 3 == 0)//1
						{
							transform->position.x = 170;
							transform->position.y = 130;
							//transform->velocity.x = -1;
							//transform->velocity.y = 1;
						}
						else if (ballPosition % 3 == 1)//2
						{
							transform->position.x = 150;
							transform->position.y = 150;
							//transform->velocity.x = 1;
							//transform->velocity.y = -1;
						}
						else//3-ballPosition
						{
							transform->position.x = 130;
							transform->position.y = 170;
						}
					}
					break;
				}
				default:
					break;
				}
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			if (Collision::hitCount <= 3)
			{
				if (transform->position.x == (tempXBall+3) && transform->position.y == (tempYBall+3))
				{
					transform->velocity.y = 0;
					transform->velocity.x = 0;
				}
				else
				{
					switch (Game::event.key.keysym.sym)
					{
					case SDLK_KP_ENTER:
						Map::startMapMovement = true;
						if (transform->position.y >= 640 - (64 * 2)) //to bring back the ball if ghost is not hit
						{
							transform->position.x = tempXBall;
							transform->position.y = tempYBall;
							Game::ballMoving = false;
						}
						break;
					case SDLK_h:
						if (Map::startMapMovement == true && Game::ballMoving==true)// && mapReachedZero==true
						{
							transform->velocity.y = 1;
							transform->velocity.x = 1;
							//ballPosition = 0;
						}
						if (transform->position.y >= 640 - (64 * 2)) //to bring back the ball if ghost is not hit
						{
							transform->position.x = tempXBall;
							transform->position.y = tempYBall;
							Game::ballMoving = false;
						}
						break;
					case SDLK_SPACE:
						if (Map::startMapMovement == true && Game::ballMoving==false)// && mapReachedZero==true
						{
							transform->velocity.y = 0;
							transform->velocity.x = 0;
						}
						if (transform->position.y >= 640 - (64 * 2)) //to bring back the ball if ghost is not hit
						{
							transform->position.x = tempXBall;
							transform->position.y = tempYBall;
							Game::ballMoving = false;
						}
						break;
					default:
						break;
					}
				}
			}
		}

	}
	/*void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				//sprite->Play("walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("walk");
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				//sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			default:
				break;

			}
		}
	}*/
}; 
