#pragma once
#include "../Base/Base.h"

class Game :public Base 
{
private:
	int m_time;
	int m_deathcount;

public:
	Game();
	void Update();
};