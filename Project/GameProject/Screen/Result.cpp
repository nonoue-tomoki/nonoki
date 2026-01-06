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

    int sec = Game::s_time_frame / DEFAULT_FPS;
    int min = sec / 60;
    sec %= 60;

    float r = 0.463f;
    float g = 0.522f;
    float b = 1.0f;

    FONT_T()->Draw(960, 480, r, g, b, "Result Clear");

    FONT_T()->Draw(960, 540, r, g, b, "Time : %02d:%02d", min, sec);

    FONT_T()->Draw(960, 600, r, g, b, "Deaths : %d", Game::s_death_count);
}


void Result::Update()
{
    if (PUSH(CInput::eButton1)) {
        KillAll();
        Base::Add(new Title());
        return;
    }
}
