#include "Title.h"
#include "../Game/Game.h"

Title::Title():Base(eType_Scene)
{

}

void Title::Draw()
{

}

void Title::Update()
{
	if (PUSH(CInput::eButton3))
	{
		KillAll();
		Base::Add(new Game());
	}
}