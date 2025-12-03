#pragma once
#include "Base/Base.h"
#include "GLLibrary/CInput.h"
#include "GLLibrary/CImage.h"
#include "GLLibrary/Utility.h"
#include "Map.h"

#define DASH_SPEED 10
#define WALL_SLIDE_SPEED 1
#define MOVE_SPEED 4
#define JUMP_POWER 10
#define WALL_KICK_POWER_X 10
#define WALL_KICK_POWER_Y 12

class Player : public Base {
private:
    enum {
        eAnimIdle = 0,
        eAnimRun,
        eAnimJumpUp,
        eAnimJumpDown,
        eAnimDown,
    };

    enum {
        eState_Idle,
        eState_Jump,
        eState_WallGrab,
        eState_Down,
    };
    int m_state;

    CImage m_img;
    bool m_flip;
    bool m_is_ground;
    int m_wall_dir;
    int m_jump_count;
    const static int MAX_JUMP = 2;
    bool m_can_dash;

    void PlayerDash();

public:
    Player(const CVector2D& pos, bool flip);
    ~Player() override;

    void Update() override;
    void Draw() override;
    void Collision(Base* b) override;

    void StateIdle();
    void StateJump();
    void StateWallGrab();
    void StateDown();
};