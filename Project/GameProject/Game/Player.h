#pragma once
#include "../Base/Base.h"

class Player :public Base {
private:
    enum {
        eAnimIdle = 0,
        eAnimRun,
        eAnimJumpUp,
        eAnimJumpDown,
        eAnimAttack01,
        eAnimDamage,
        eAnimDown,
    };

    enum {
        eState_Idle,
        eState_Grab,
        eState_Dash,
        eState_Down,
    };


	int m_state;

	CImage m_img;
	bool m_flip;
	bool m_is_ground;


public:
	Player(const CVector2D& pos, bool flip);
	void Draw();
	void Update();
	void Collision(Base* b);


	void StateIdle();
	void StateRun();
	void StateDash();
	void StateGrab();
	void StateDown();
};
