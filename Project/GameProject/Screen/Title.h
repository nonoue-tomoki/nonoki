#pragma once
#include "Base/Base.h"

class Title :public Base {
	
private:
	CImage m_img;
	CImage m_title;

	CFont m_title_text;
public:
	Title();
	void Draw();
	void Update();
};