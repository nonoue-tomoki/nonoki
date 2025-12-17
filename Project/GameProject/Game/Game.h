#pragma once
#include "Base/Base.h"

#define MAP_TIP_SIZE 60
#define MAP_WIDTH 32
#define MAP_HEIGHT 19
#define SPAWN_X_LEFT    (1.5f * MAP_TIP_SIZE)   
#define SPAWN_Y_BOTTOM  (16.5f * MAP_TIP_SIZE)

class Game :public Base 
{
private:
	int m_time = 0;
	int m_deathcount = 0;

	static int s_next_area_id;
	static CVector2D s_next_pos;

	static int s_current_area_id;
	static CVector2D s_restart_pos;

	static void LoadArea(int area_id, const CVector2D& player_pos);

public:
	Game();
	void Update();
};