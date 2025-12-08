#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "Map.h"
#include "../Screen/Result.h"
#include "../Screen/Title.h"

Game::Game() :Base(eType_UI) 
{

	Base::Add(new Map());
	Base::Add(new Player(CVector2D(2.5f * TILE_SIZE, 15.5f * TILE_SIZE), false));
	Base::Add(new Enemy(CVector2D(10.5f * TILE_SIZE, 15.5f * TILE_SIZE)));
	Base::Add(new Goal(CVector2D(6.5f * TILE_SIZE, 2.5f * TILE_SIZE)));

}

void Game::Update()
{
	m_time++;

	Base* p = Base::FindObject(eType_Player);
	if (p == NULL) {
		if (PUSH(CInput::eButton3)) {
			KillAll();
			m_deathcount++;
			Base::Add(new Game());
		}
	}
}
