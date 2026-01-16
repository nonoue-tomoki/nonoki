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

	static int s_next_area_id;
	static CVector2D s_next_pos;

	static int s_current_area_id;
	static CVector2D s_restart_pos;

	static void LoadArea(int area_id, const CVector2D& player_pos);

	void Restart();

public:
	static int s_death_count;
	static int s_time_frame;
	static int s_moon_count;

	Game();
	void Update();
};