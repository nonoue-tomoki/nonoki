#pragma once
#include "../Base/Base.h"

class Game :public Base 
{
private:
	int m_time;


public:
	Game();
	void Update();
};