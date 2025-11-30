#pragma once
#include "../Base/Base.h"

class Block :public Base 
{
private:
	CImage m_img;

public:
	Block(CVector2D pos, float width, float height);

	virtual ~Block() {}

	void Update() override;

	void Draw() override;

	void Collision(Base* b) override {}
};