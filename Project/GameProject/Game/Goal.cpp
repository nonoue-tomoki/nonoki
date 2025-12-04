#include "Goal.h"
Goal::Goal(const CVector2D& pos) :Base(eType_Goal)
{
	m_img = COPY_RESOURCE("Goal", CImage);
	m_pos = pos;
	m_img.SetSize(60, 120);
	m_img.SetCenter(30, 120);
	m_rect = CRect(-30, -120, 30, 0);
	m_is_goal = false;
}

void Goal::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}
