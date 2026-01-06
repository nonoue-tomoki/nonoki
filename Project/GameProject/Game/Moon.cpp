#include "Moon.h"

Moon::Moon(const CVector2D& pos)
    : Base(eType_Object)
{
    m_pos = pos;
    m_rect = CRect(-16, -16, 16, 16);

    m_img = COPY_RESOURCE("Moon", CImage);
    m_img.SetSize(64, 64);
    m_img.SetCenter(32, 32);
}

void Moon::Update() {}

void Moon::Draw()
{
    m_img.SetPos(GetScreenPos(m_pos));
    m_img.Draw();
}