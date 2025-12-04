#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "Item.h"
#include "Map.h"
#include "../Screen/Result.h"
#include "../Screen/Title.h"

Game::Game() :Base(eType_UI) 
{

	float start_x = 2.5f * TILE_SIZE;
	float start_y = 15.5f * TILE_SIZE;

	Base::Add(new Map());
	Base::Add(new Player(CVector2D(start_x, start_y), false));
	Base::Add(new Enemy(CVector2D(500, 900)));
	Base::Add(new Goal(CVector2D(600, 900)));
}

void Game::Update()
{
	m_time++;

}