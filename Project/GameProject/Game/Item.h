#pragma once
#include "../Base/Base.h"

class Item :public Base {
private:
	CImage m_img;

public:
	Item(const CVector2D& p);
	void Draw();
	void Update();
	void Collision(Base* b);
};
