#include "Block.h"

Block::Block(CVector2D pos, float width, float height) : Base(eType_Field)
{
	m_pos = pos;
	m_vec = CVector2D(0, 0);

	m_rect.m_left = -width / 2.0f;
	m_rect.m_right = width / 2.0f;
	m_rect.m_top = height / 2.0f;
	m_rect.m_bottom = -height / 2.0f;
}

void Block::Update()
{
    m_vec = CVector2D(0, 0);
}

void Block::Draw()
{
    CVector4D color(0.0f, 0.7f, 0.0f, 1.0f);

    CVector2D screenPos = Base::GetScreenPos(m_pos);

    float width = m_rect.m_right - m_rect.m_left;
    float height = m_rect.m_top - m_rect.m_bottom;

    Utility::DrawQuad(
        CVector2D(screenPos.x + m_rect.m_left, screenPos.y + m_rect.m_top),
        CVector2D(width, height),
        color);
}