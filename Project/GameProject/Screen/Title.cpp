#include "Title.h"
#include "../Game/Game.h"

Title::Title():Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_title = COPY_RESOURCE("Title", CImage);
	m_img = COPY_RESOURCE("Background", CImage);

	m_title.SetSize(480, 160);
	m_title.SetCenter(240, 80);

	m_img.SetSize(1920, 1080);

}

void Title::Draw()
{
	m_title.SetPos(960, 300);

	m_img.Draw();
	m_title.Draw();

	m_title_text.Draw(840, 560, 0.463f, 0.522f, 1.0f, "Push C");
}

void Title::Update()
{
	if (PUSH(CInput::eButton3))
	{
		KillAll();

		Game::s_time_frame = 0;
		Game::s_death_count = 0;
		Game::s_moon_count = 0;
		
		Base::Add(new Game());
	}
}