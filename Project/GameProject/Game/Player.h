#pragma once
#include "../Base/Base.h"

enum class PlayerState
{
	Normal,
	Dash,
	Climb,
};

class Player :public Base
{
public:
	Player(const CVector2D& pos, bool flip);

	void Update() override;
	void Draw() override;
	void Collision(Base* b) override;

private:
	void UpdateNormal();
	void UpdateDash();
	void UpdateClimb();

	void UpdateInputState();

private:
	float m_speed;
	float m_jumpPower;
	float m_dashSpeed;
	float m_climbSpeed;

	int m_dashTimer;
	int m_dashMaxTime;
	bool m_canDash;
	CVector2D m_dashDir;

	bool m_is_wall;
	int m_wallDir;

	PlayerState m_state;
	bool m_is_ground;
	bool m_flip;
	CImage m_img;

	bool m_prevJumpHold;
	bool m_prevDashHold;
	bool m_isJumpTrigger;
	bool m_isDashTrigger;
};