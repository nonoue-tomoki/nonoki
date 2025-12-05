#pragma once
#include "Base/Base.h"

class Enemy :public Base {
private:
	CImage m_img;
	int m_movespeed;
	int m_tick;
public:
	Enemy(const CVector2D pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};