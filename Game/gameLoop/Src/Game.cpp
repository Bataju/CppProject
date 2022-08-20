#include "Game.h"
#include "textureManager.h"
#include "GameObject.h"
#include "Map.h"
#include"ECS/Components.h"
#include "Vector2D.h"
#include"Collision.h"

Map* map;
Manager manager;

int Collision::hitCount = 0;
int Game::updateCounter = 0;
bool Map::startMapMovement = false;
bool Game::ballMoving = false;
bool Game::isRunning = false;

SDL_Renderer* Game::renderer = nullptr;            //we can reassign
SDL_Event Game::event;
SDL_Texture* winLoseTexture = nullptr;
SDL_Rect srcWinLose = { 0, 0, 400,300 };
SDL_Rect destWinLose = { 200, 180, 400,300 };


/*SDL_Texture* Game::startTexture = nullptr;
SDL_Texture* Game::finishTexture = nullptr;*/
/*SDL_Rect srcStart = {0, 0, 800,640};
SDL_Rect destStart = { 0, 0, 800,640 };
SDL_Rect srcFinish = { 0, 0, 800, 640 };
SDL_Rect destFinish = { 0, 0, 800, 640 }; //600=800-200 for xpos of dest rect*/

/*SDL_Rect srcStart = {0, 0, 300,640};
SDL_Rect destStart = { 0, 0, 300,640 };
SDL_Rect srcFinish = { 0, 0, 300, 640 };
SDL_Rect destFinish = { 500, 0, 300, 640 }; //600=800-200 for xpos of dest rect*/

std::vector<ColliderComponent*> Game::colliders;

auto& Player(manager.addEntity());  //creating our player
auto& Enemy(manager.addEntity());  //creating our enemy
auto& Ball(manager.addEntity());

//auto& wall(manager.addEntity());

const char* mapfile = "gameLoop/gfx/finalMapTile64.png";

enum groupLables : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


auto& tiles(manager.getGroup(groupMap));
auto& Players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& ball(manager.getGroup(groupColliders));


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}

		isRunning = true;
	}

	map = new Map();
	static int loop;

	for (loop = 0; loop < 4; loop++)
	{
		if (loop == 0 || loop == 3)
			map->LoadMap("gameLoop/gfx/startEnd.map", 5, 10, loop);
		else
			map->LoadMap("gameLoop/gfx/finalMap64.map", 25, 10, loop);
	}

	//player
	Player.addComponent<TransformComponent>(80, 85, 200, 200, 0.48);  //player component render
	Player.addComponent<SpriteComponent>("gameLoop/gfx/finalPlayer.png", true);
	//Player.addComponent<KeyboardComtroller>();
	Player.addComponent<ColliderComponent>("Player");
	Player.addGroup(groupPlayers);

	//enemy
	Enemy.addComponent<TransformComponent>(447, 447, 200, 200, 0.48);    //enemy component render
	Enemy.addComponent<SpriteComponent>("gameloop/gfx/finalEnemy.png", true);
	//Enemy.addComponent<KeyboardComtroller>();
	Enemy.addComponent<ColliderComponent>("Enemy");
	Enemy.addGroup(groupEnemies);

	//ball
	Ball.addComponent<TransformComponent>(170, 130, 200, 200, 0.16);
	//Ball.addComponent<SpriteComponent>("gameloop/gfx/ballNewDark.png", true);
	Ball.addComponent<SpriteComponent>("gameloop/gfx/powerball.png", true).Play("Move");
	Ball.addComponent<KeyboardComtroller>();
	Ball.addComponent<ColliderComponent>("Ball");
	Ball.addGroup(groupColliders);

	//wall.addComponent <TransformComponent>(100.0f, 300.0f, 300, 20, 1);
	//wall.addComponent<SpriteComponent>("dev/water.png");
	//wall.addComponent<ColliderComponent>("Wall");
	//wall.addGroup(groupMap);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	if (Map::startMapMovement == true)
	{
		Game::updateCounter++;
	}
	std::cout << Game::updateCounter << std::endl;
	//backround moving 
	Vector2D pVel = Player.getComponent<TransformComponent>().velocity;
	int pSpeed = Player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		if (Map::startMapMovement == true)
		{
			t->getComponent<TileComponent>().destRect.x += -2;//-(pVel.x * pSpeed);
			/**f (t->getComponent<TileComponent>().destRect.x == 0)
			{
				mapReachedZero = true;//TRUE FOREVER
			}*/
		}

		if (Collision::hitCount >= 3)
		{
			Enemy.getComponent<SpriteComponent>().Play("Dead");
			break;
		}
		else if (Game::updateCounter >= 1500)
		{
			Enemy.getComponent<TransformComponent>().velocity.x = 1;
			break;
		}

		else
			continue;
	}

	if (Collision::AABB(Ball.getComponent<ColliderComponent>().collider, Enemy.getComponent<ColliderComponent>().collider))
	{
		/*ballMoving = false;
		if (hitCount % 2 == 0)
		{
			Enemy.getComponent<TransformComponent>().position.x = 447;
			Enemy.getComponent<TransformComponent>().position.y = 447;
		}
		else
		{
			Enemy.getComponent<TransformComponent>().position.x = 467;
			Enemy.getComponent<TransformComponent>().position.y = 427;
		}
		Ball.getComponent<TransformComponent>().position.x = 170;
		Ball.getComponent<TransformComponent>().position.y = 130;
		Ball.getComponent<TransformComponent>().velocity.x = 0;
		Ball.getComponent<TransformComponent>().velocity.y = 0;*/
		Game::ballMoving = false;
		Ball.getComponent<TransformComponent>().position.x = 170;
		Ball.getComponent<TransformComponent>().position.y = 130;
		Ball.getComponent<TransformComponent>().velocity.x = 0;
		Ball.getComponent<TransformComponent>().velocity.y = 0;
	}

	//if (Collision::AABB(Player.getComponent<ColliderComponent>().collider,
	//	wall.getComponent<ColliderComponent>().collider))
	//{
	//	Player.getComponent<TransformComponent>().scale = 1;
	//	Player.getComponent<TransformComponent>().velocity * -1;
	//	std::cout << "wall hit!" << std::endl;
	//}
	//std::cout << Enemy.getComponent < TransformComponent>().position.x << " , " << Enemy.getComponent < TransformComponent>().position.y << std::endl;

	//for (auto cc : colliders)
	//{
	//	Collision::AABB(Player.getComponent<ColliderComponent>(), *cc);
	//}
}


void Game::render()
{
	SDL_RenderClear(renderer);
	/*startTexture = TextureManager::LoadTexture("gameLoop/gfx/startForest.png");
	TextureManager::Draw(startTexture, srcStart, destStart, SDL_FLIP_NONE);
	if (updateCounter >= 1200)
	{
		finishTexture = TextureManager::LoadTexture("gameLoop/gfx/endForest.png");
		TextureManager::Draw(finishTexture, srcFinish, destFinish, SDL_FLIP_NONE);
	}*/
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : Players)
	{
		p->draw();
	}
	for (auto& b : ball)
	{
		b->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	if (Collision::hitCount >= 3)
	{
		winLoseTexture = TextureManager::LoadTexture("gameLoop/dev/winFinal.png");
		TextureManager::Draw(winLoseTexture, srcWinLose, destWinLose, SDL_FLIP_NONE);
	}
	if (updateCounter >= 1600 && Collision::hitCount < 3)
	{
		winLoseTexture = TextureManager::LoadTexture("gameLoop/dev/loseFinal.png");
		TextureManager::Draw(winLoseTexture, srcWinLose, destWinLose, SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);///xpos + 200
	tile.addGroup(groupMap);
}

//single tile component system
//void Game::addTile(int id, int x, int y)
//{
//	auto& tile(manager.addEntity());
//	tile.addComponent<TileComponent>(x,y,64,64,id);
//	tile.addGroup(groupMap);
//}