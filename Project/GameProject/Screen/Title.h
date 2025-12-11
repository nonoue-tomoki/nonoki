#pragma once
#include "Base/Base.h"

class Title :public Base {
	
private:
	CImage m_img;

public:
	Title();
	void Draw();
	void Update();
};