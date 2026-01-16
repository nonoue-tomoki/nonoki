#include "Player.h"
#include "Moon.h"
#include "Map.h"
#include "AreaChange.h"
#include "Game.h"
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
    eState_WallGrab,
    eState_Down,
};

static TexAnim _idle[] = {
    { 0,2 },
};

static TexAnim _run[] = {
    { 10,2 },
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

    m_dash_keep = 0;

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

    m_dash_keep = 10;
}

void Player::StateIdle() {
    if (PUSH(CInput::eButton2)) {
        PlayerDash();
        m_state = eState_Jump;
        return;
    }

    bool input_lr = HOLD(CInput::eLeft) || HOLD(CInput::eRight);
    if (input_lr) {
        m_dash_keep = 0;
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
        if (m_dash_keep <= 0) {
            float friction = (m_ground_tile == TILE_ICE) ? ICE_FRICTION : GROUND_FRICTION;
            m_vec.x *= friction;
            if (fabs(m_vec.x) < 0.05f) m_vec.x = 0.0f;
        }
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

    if (m_dash_keep > 0) {
        m_dash_keep--;
    }

    switch (m_state) {
    case eState_Idle:
        StateIdle();
        m_vec.y += GRAVITY;
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

    const float margin_x = 120.0f;
    const float margin_y = 240.0f;

    if (m_pos.x < -margin_x || m_pos.x > SCREEN_WIDTH + margin_x ||
        m_pos.y < -margin_y || m_pos.y > SCREEN_HEIGHT + margin_y) {
        SetKill();
        return;
    }

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
            Base::Add(new Result(true));
        }
    }

    if (b->m_type == eType_Object) {
        if (Base::CollisionRect(this, b)) {
            Moon* moon = dynamic_cast<Moon*>(b);
            if (moon) {
                Game::s_moon_count++;
                b->SetKill();
            }
        }
    }

    if (b->m_type == eType_Enemy) {
        if (Base::CollisionRect(this, b)) {
            SetKill();
        }
    }

    if (b->m_type == eType_Map) {
        if (Map* m = dynamic_cast<Map*>(b)) {
            if (m_state == eState_WallGrab && m_wall_dir != 0) {
                int side = m->CollisionRect(CVector2D(m_pos.x + (float)m_wall_dir * 4.0f, m_pos.y), m_rect);
                if (side != TILE_SOLID) {
                    m_state = eState_Jump;
                    m_wall_dir = 0;
                }
            }

            int t;

            t = m->CollisionRect(CVector2D(m_pos.x, m_pos_old.y), m_rect);
            if (t != 0) {

                if (t == 4 || t == 5) {
                    m_next_area = true;
                    int current_area = m->GetAreaID();

                    AreaChange::CalculateNextArea(
                        current_area,
                        t,
                        m_pos,
                        m_next_area_id,
                        m_next_pos
                    );
                    return;
                }

                int hit_dir = 0;
                if (m_pos.x > m_pos_old.x) hit_dir = 1;
                else if (m_pos.x < m_pos_old.x) hit_dir = -1;

                m_pos.x = m_pos_old.x;
                m_vec.x = 0;

                if (t == TILE_SPIKE) {
                    SetKill();
                }

                if (t == TILE_SOLID && PUSH(CInput::eButton1) && hit_dir != 0) {
                    m_state = eState_WallGrab;
                    m_wall_dir = hit_dir;
                    m_flip = (hit_dir == -1);
                    m_vec.y = 0;
                    return;
                }

                if (m_state == eState_Jump && t == TILE_SOLID && hit_dir != 0) {
                    if ((hit_dir == 1 && HOLD(CInput::eRight)) || (hit_dir == -1 && HOLD(CInput::eLeft))) {
                        m_state = eState_WallGrab;
                        m_wall_dir = hit_dir;
                        m_flip = (hit_dir == -1);
                        return;
                    }
                }
            }

            float vy_before = m_vec.y;

            t = m->CollisionRect(CVector2D(m_pos_old.x, m_pos.y), m_rect);
            if (t != 0) {

                if (t == 4 || t == 5) {
                    m_next_area = true;
                    int current_area = m->GetAreaID();

                    AreaChange::CalculateNextArea(
                        current_area,
                        t,
                        m_pos,
                        m_next_area_id,
                        m_next_pos
                    );
                    return;
                }

                m_pos.y = m_pos_old.y;

                if (t == TILE_SPRING && vy_before >= 0.0f) {
                    m_vec.y = -SPRING_POWER;
                    m_state = eState_Jump;
                    m_is_ground = false;
                    m_jump_count = 0;
                    m_can_dash = true;
                    return;
                }

                m_vec.y = 0;

                if (vy_before >= 0.0f) {
                    m_is_ground = true;
                    m_ground_tile = t;
                    m_jump_count = 0;
                    m_wall_dir = 0;
                    m_can_dash = true;
                    if (m_state == eState_WallGrab || m_state == eState_Jump) {
                        m_state = eState_Idle;
                    }
                }

                if (t == TILE_SPIKE) {
                    SetKill();
                }
            }
        }
    }
}
