#include "Game.h"
#include "Player.h"
#include "Item.h"
#include "Map.h"
#include "Block.h"
#include "../Screen/Result.h"
#include "../Screen/Title.h"

Game::Game() :Base(eType_UI) 
{

}

void Game::Update()
{
	m_time++;

}