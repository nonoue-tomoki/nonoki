#pragma once
#include "Base/Base.h"

class Game :public Base 
{
private:
	int m_time = 0;
	int m_deathcount = 0;

public:
	Game();
	void Update();
};