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
enum class PlayerState
{
	Normal,
	Dash,
	Climb,
};







    enum {
        eState_Idle,
        eState_Grab,
        eState_Dash,
        eState_Down,
    };
class Player :public Base
{
public:
	Player(const CVector2D& pos, bool flip);

	void Update() override;
	void Draw() override;
	void Collision(Base* b) override;

	int m_state;
private:
	void UpdateNormal();
	void UpdateDash();
	void UpdateClimb();

	CImage m_img;
	bool m_flip;
	bool m_is_ground;
	void UpdateInputState();

private:
	float m_speed;
	float m_jumpPower;
	float m_dashSpeed;
	float m_climbSpeed;

public:
	Player(const CVector2D& pos, bool flip);
	void Draw();
	void Update();
	void Collision(Base* b);
	int m_dashTimer;
	int m_dashMaxTime;
	bool m_canDash;
	CVector2D m_dashDir;


	bool m_is_wall;
	int m_wallDir;

	void StateIdle();
	void StateRun();
	void StateDash();
	void StateGrab();
	void StateDown();
};
	PlayerState m_state;
	bool m_is_ground;
	bool m_flip;
	CImage m_img;

	bool m_prevJumpHold;
	bool m_prevDashHold;
	bool m_isJumpTrigger;
	bool m_isDashTrigger;
};