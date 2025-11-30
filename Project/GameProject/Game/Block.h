#pragma once
#include "../Base/Base.h"

class Block :public Base {
	
private:
	CImage m_img;

public:
	Block();
	void Draw();
	void Update();
	void Collision(Base* b);
};