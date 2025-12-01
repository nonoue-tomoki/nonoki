#include "Player.h"
#include "Map.h"

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

Player::Player(const CVector2D& p, bool flip) :
    Base(eType_Player) {
    m_img = COPY_RESOURCE("Player", CImage);
    m_pos_old = m_pos = p;

    m_img.SetSize(60, 60);
    m_img.SetCenter(30, 60);

    m_flip = flip;

    m_state = eState_Idle;

    m_is_ground = false;

    m_rect = CRect(-16, -48, 16, 0);

    m_img.AttachAnimationData(_anim_data, TILE_SIZE, TILE_SIZE);
    m_img.ChangeAnimation(eAnimIdle, true, 0, false);
}

Player::~Player() {
}

void Player::StateIdle() {
    const float move_speed = 4;
    const float jump_pow = 10;

    if (HOLD(CInput::eLeft)) {
        m_vec.x = -move_speed;
        m_flip = true;
    }
    else if (HOLD(CInput::eRight)) {
        m_vec.x = move_speed;
        m_flip = false;
    }
    else {
        m_vec.x = 0;
    }

    if (m_is_ground && PUSH(CInput::eButton3)) {
        m_vec.y = -jump_pow;
        m_is_ground = false;
        m_state = eState_Jump;
        return;
    }

    if (!m_is_ground && m_vec.y > 0) {
        m_state = eState_Jump;
        return;
    }
}

void Player::StateJump() {
    const float move_speed = 4;

    if (HOLD(CInput::eLeft)) {
        m_vec.x = -move_speed;
        m_flip = true;
    }
    else if (HOLD(CInput::eRight)) {
        m_vec.x = move_speed;
        m_flip = false;
    }
}

void Player::StateDown() {
    SetKill();
}


void Player::Update() {
    m_pos_old = m_pos;

    if (m_state != eState_Down) {
        m_vec.y += GRAVITY;
    }

    switch (m_state) {
    case eState_Idle:
        StateIdle();
        break;
    case eState_Jump:
        StateJump();
        break;
    case eState_Down:
        StateDown();
        break;
    }

    m_pos += m_vec;
    
    /*
    m_scroll.x = m_pos.x - SCREEN_WIDTH / 2;
    m_scroll.y = m_pos.y - SCREEN_HEIGHT / 2;
    */

    m_scroll = CVector2D(0, 0);

    m_is_ground = false;

    if (m_is_ground) {
        if (m_vec.x != 0) {
            m_img.ChangeAnimation(eAnimRun);
        }
        else {
            m_img.ChangeAnimation(eAnimIdle);
        }
    }
    else {
        if (m_vec.y < 0) {
            m_img.ChangeAnimation(eAnimJumpUp, false, 0, false);
        }
        else {
            m_img.ChangeAnimation(eAnimJumpDown, false, 0, false);
        }
    }

    m_img.UpdateAnimation();
}

void Player::Draw() {
    m_img.SetPos(GetScreenPos(m_pos));
    m_img.SetFlipH(m_flip);
    m_img.Draw();
    DrawRect();
}

void Player::Collision(Base* b) {
    if (m_state == eState_Down) return;

    if (b->m_type == eType_Map) {

        if (Map* m = dynamic_cast<Map*>(b)) {
            int collide_dir;

            CVector2D pos_x_only = CVector2D(m_pos.x, m_pos_old.y);
            collide_dir = m->CollisionRect(pos_x_only, m_rect);

            if (collide_dir != 0) {
                m_pos.x = m_pos_old.x;
                m_vec.x = 0;
            }

            CVector2D pos_y_only = CVector2D(m_pos.x, m_pos.y);
            collide_dir = m->CollisionRect(pos_y_only, m_rect);

            if (collide_dir != 0) {
                m_pos.y = m_pos_old.y;
                m_vec.y = 0;

                if (m_vec.y >= 0) {
                    m_is_ground = true;
                    if (m_state == eState_Jump) {
                        m_state = eState_Idle;
                    }
                }
            }
        }
        return;
    }
}