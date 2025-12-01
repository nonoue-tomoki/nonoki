#pragma once
#include "Base/Base.h"
#include "GLLibrary/CInput.h"
#include "GLLibrary/CImage.h"
#include "GLLibrary/Utility.h"

#define PLAYER_WIDTH (64)
#define PLAYER_HEIGHT (64)

class Player : public Base {
private:
    enum {
        eState_Idle,
        eState_Jump,
        eState_Down,
    };
    int m_state;

    CImage m_img;
    bool m_flip;
    bool m_is_ground;

public:
    Player(const CVector2D& pos, bool flip);
    ~Player() override;

    void Update() override;
    void Draw() override;
    void Collision(Base* b) override;

    void StateIdle();
    void StateJump();
    void StateDown();
};