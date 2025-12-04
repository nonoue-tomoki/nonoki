#pragma once
#include "../Base/Base.h"

class Result :public Base {

private:
	CImage m_img;

public:
	Result();
	void Draw();
	void Update();
};