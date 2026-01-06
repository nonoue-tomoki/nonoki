#include "Result.h"
#include "Title.h"
#include "../Game/Game.h"

Result::Result(bool clear)
    : Base(eType_Scene),
    m_font("C:\\Windows\\Fonts\\msgothic.ttc", 64),
    m_clear(clear)
{
    m_img = COPY_RESOURCE("Background", CImage);
    m_img.SetSize(1920, 1080);
}

void Result::Draw()
{
    m_img.Draw();

    if (m_clear) {
        m_font.Draw(760, 360, 0.463f, 0.522f, 1.0f, "CLEAR");
    }

    m_font.Draw(840, 560, 0.463f, 0.522f, 1.0f, "Title : Z");
}

void Result::Update()
{
    if (PUSH(CInput::eButton1)) {
        KillAll();
        Base::Add(new Title());
        return;
    }
}
