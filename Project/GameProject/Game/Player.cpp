#include "Player.h"
#include "Map.h"
#include "Screen/Result.h"
#include <cmath>

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
    eState_Down,
};
    
static TexAnim _idle[] = {
    { 0,2 }, 
    { 1,2 }, 
    { 2,2 }, 
    { 3,2 },
    { 4,2 },
};

static TexAnim _run[] = {
    { 10,2 },
    { 11,2 }, 
    { 12,2 },
    { 13,2 }, 
    { 14,2 }, 
};

static TexAnim _jump_up[] = {
    { 20, 1 },
};

static TexAnim _jump_down[] = {
    { 30, 1 },
};

static TexAnimData _anim_data[] = {
    ANIMDATA(_idle),
    ANIMDATA(_run),
    ANIMDATA(_jump_up),
    ANIMDATA(_jump_down),
};

Player::Player(const CVector2D& pos, bool flip) :
    Base(eType_Player) {
    m_img = COPY_RESOURCE("Player", CImage);
    m_pos_old = m_pos = pos;

    m_img.SetSize(60, 60);
    m_img.SetCenter(30, 60);
    m_flip = flip;
    m_state = eState_Idle;
    m_is_ground = false;
    m_wall_dir = 0;
    m_jump_count = 0;
    m_can_dash = true;

    m_rect = CRect(-16, -48, 16, 0);

    m_img.AttachAnimationData(_anim_data, 60, 60);
    m_img.ChangeAnimation(eAnimIdle, true, 0, false);
}

Player::~Player() {
}

void Player::PlayerDash() {
    if (!m_can_dash) return;

    m_can_dash = false;

    bool input_left = HOLD(CInput::eLeft);
    bool input_right = HOLD(CInput::eRight);
    bool input_up = HOLD(CInput::eUp);
    bool input_down = HOLD(CInput::eDown);

    CVector2D dash_vec(0, 0);

    if (input_right) {
        dash_vec.x = 1.0f;
    }
    else if (input_left) {
        dash_vec.x = -1.0f;
    }

    if (input_up) {
        dash_vec.y = -1.0f;
    }
    else if (input_down) {
        dash_vec.y = 1.0f;
    }

    if (dash_vec.x != 0 || dash_vec.y != 0) {
        float length = sqrtf(dash_vec.x * dash_vec.x + dash_vec.y * dash_vec.y);

        if (length > 0.0f) {
            dash_vec.x /= length;
            dash_vec.y /= length;

            dash_vec.x *= DASH_SPEED;
            dash_vec.y *= DASH_SPEED;
        }

        m_vec = dash_vec;

        if (m_vec.x > 0) m_flip = false;
        if (m_vec.x < 0) m_flip = true;

    }
    else {
        float dash_dir = m_flip ? -1.0f : 1.0f;
        m_vec.x = dash_dir * DASH_SPEED;
    }
}


void Player::StateIdle() {
    if (PUSH(CInput::eButton2)) {
        PlayerDash();
        m_state = eState_Jump;
        return;
    }

    if (HOLD(CInput::eLeft)) {
        m_vec.x = -MOVE_SPEED;
        m_flip = true;
    }
    else if (HOLD(CInput::eRight)) {
        m_vec.x = MOVE_SPEED;
        m_flip = false;
    }
    else {
        m_vec.x = 0;
    }

    if (PUSH(CInput::eButton3)) {
        m_vec.y = -JUMP_POWER;
        m_state = eState_Jump;
        m_jump_count = 1;
        return;
    }
}

void Player::StateJump() {
    if (PUSH(CInput::eButton2)) {
        PlayerDash();
        return;
    }

    if (std::abs(m_vec.x) < MOVE_SPEED) {
        if (HOLD(CInput::eLeft)) {
            m_vec.x = -MOVE_SPEED;
            m_flip = true;
        }
        else if (HOLD(CInput::eRight)) {
            m_vec.x = MOVE_SPEED;
            m_flip = false;
        }
    }
    else {
        m_vec.x *= 0.995;
    }

    if (PUSH(CInput::eButton3) && m_jump_count < MAX_JUMP) {
        m_vec.y = -JUMP_POWER;
        m_jump_count++;
    }
}

void Player::StateWallGrab() {
    m_vec.x = 0;
        
    if (PUSH(CInput::eButton3)) {
        m_vec.x = -m_wall_dir * WALL_KICK_POWER_X;
        m_vec.y = -WALL_KICK_POWER_Y;
        m_state = eState_Jump;
        m_wall_dir = 0;
        m_jump_count = 1;
        m_can_dash = true;
        return;
    }

    if (HOLD(CInput::eButton1)) {
        m_vec.y = 0;

        if (HOLD(CInput::eUp)) {
            m_vec.y = -WALL_SLIDE_SPEED * 1.5f;
        }
        else if (HOLD(CInput::eDown)) {
            m_vec.y = WALL_SLIDE_SPEED * 2.0f;
        }
    }
    else {
        bool input_opposite = (m_wall_dir == 1 && HOLD(CInput::eLeft)) ||
            (m_wall_dir == -1 && HOLD(CInput::eRight));

        if (FREE(CInput::eButton1) || input_opposite || (m_wall_dir == 1 && FREE(CInput::eRight)) || (m_wall_dir == -1 && FREE(CInput::eLeft))) {
            m_wall_dir = 0;
            m_state = eState_Jump;
            return;
        }

        m_vec.y += GRAVITY;

        if (HOLD(CInput::eUp)) {
            m_vec.y = -WALL_SLIDE_SPEED * 1.5f;
        }
        else if (HOLD(CInput::eDown)) {
            m_vec.y = WALL_SLIDE_SPEED * 2.0f;
        }
    }

    m_img.ChangeAnimation(eAnimJumpUp, false, 0, false);
}

void Player::StateDown() {
}


void Player::Update() {
    m_pos_old = m_pos;

    m_is_ground = false;

    switch (m_state) {
    case eState_Idle:
        StateIdle();
        if (m_state != eState_Idle) m_vec.y += GRAVITY;
        break;
    case eState_Jump:
        StateJump();
        m_vec.y += GRAVITY;
        break;
    case eState_WallGrab:
        StateWallGrab();
        break;
    case eState_Down:
        StateDown();
        break;
    }

    m_pos += m_vec;

    if (m_state == eState_Idle || m_state == eState_Jump) {
        if (m_is_ground) {
            m_img.ChangeAnimation(m_vec.x != 0 ? eAnimRun : eAnimIdle);
        }
        else {
            m_img.ChangeAnimation(m_vec.y < 0 ? eAnimJumpUp : eAnimJumpDown, false, 0, false);
        }
    }

    m_img.UpdateAnimation();
}

void Player::Draw() {
    m_img.SetPos(GetScreenPos(m_pos));
    m_img.SetFlipH(m_flip);
    m_img.Draw();
}


void Player::Collision(Base* b) {
    if (b->m_type == eType_Goal) {
        if (Base::CollisionRect(this, b)) {
            KillAll();
            Base::Add(new Result());
        }
    }
    if (b->m_type == eType_Enemy) {
        if (Base::CollisionRect(this, b)) {
            SetKill();
        }
    }
    if (b->m_type == eType_Map) {
        if (Map* m = dynamic_cast<Map*>(b)) {
            int t;

            t = m->CollisionRect(CVector2D(m_pos.x, m_pos_old.y), m_rect);
            if (t != 0) {
                m_pos.x = m_pos_old.x;
                m_vec.x = 0;

                if (t > 1) {
                    SetKill();
                }
                if (PUSH(CInput::eButton1)) {
                    m_state = eState_WallGrab;
                    m_wall_dir = t;
                    m_flip = (t == 1);
                    m_vec.y = 0;
                    return;
                }

                if (m_state == eState_Jump) {
                    if ((t == 1 && HOLD(CInput::eLeft)) || (t == -1 && HOLD(CInput::eRight))) {
                        m_state = eState_WallGrab;
                        m_wall_dir = t;
                        m_flip = (t == 1);
                        return;
                    }
                }
            }

            t = m->CollisionRect(CVector2D(m_pos_old.x, m_pos.y), m_rect);
            if (t != 0) {
                m_pos.y = m_pos_old.y;
                m_vec.y = 0;
                if (m_vec.y >= 0) {
                    m_is_ground = true;
                    m_jump_count = 0;
                    m_wall_dir = 0;
                    m_can_dash = true;
                    if (m_state == eState_WallGrab || m_state == eState_Jump) {
                        m_state = eState_Idle;
                    }
                }
            }
        }
    }
}