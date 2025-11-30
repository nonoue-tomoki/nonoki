#pragma once
#include "../Base/Base.h"

class Map :public Base {
	CImage m_img;

	Map(const CVector2D& pos);
	void Draw();
	void Update();
	void Collision(Base* b);
};