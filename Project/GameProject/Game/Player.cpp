#include "Player.h"
#include "./GLLibrary/CInput.h"
const float MOVE_SPEED = 5.0f; 
const float JUMP_POWER = 12.0f;
const float DASH_SPEED = 15.0f;
const int   DASH_TIME = 10;
const float CLIMB_SPEED = 3.0f;
const float WALL_JUMP_X = 8.0f;


Player::Player(const CVector2D& pos, bool flip) :Base(eType_Player)
{
    m_rect = CRect(-64, -128, 64, 0);
    m_img.SetSize(128, 128);
    m_img.SetCenter(64, 128);

    m_pos = pos;

    // ƒpƒ‰ƒ[ƒ^‰Šú‰»
    m_speed = MOVE_SPEED;
    m_jumpPower = JUMP_POWER;
    m_dashSpeed = DASH_SPEED;
    m_dashMaxTime = DASH_TIME;
    m_climbSpeed = CLIMB_SPEED;

    m_state = PlayerState::Normal;
    m_canDash = true;
    m_is_ground = false;
    m_is_wall = false;
    m_wallDir = 0;
    m_flip = flip;
}

void Player::Update()
{
    switch (m_state) {
    case PlayerState::Normal: UpdateNormal(); break;
    case PlayerState::Dash:   UpdateDash();   break;
    case PlayerState::Climb:  UpdateClimb();  break;
    }

    m_pos += m_vec;
    m_vec.y -= GRAVITY;

    Base::m_scroll = m_pos - CVector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    m_is_ground = false;
    m_is_wall = false;
}

void Player::UpdateInputState()
{
    bool currentJumpHold = HOLD(CInput::eButton3);
    m_isJumpTrigger = (currentJumpHold && !m_prevJumpHold);
    m_prevJumpHold = currentJumpHold;

    bool currentDashHold = HOLD(CInput::eButton2);
    m_isDashTrigger = (currentDashHold && !m_prevDashHold);
    m_prevDashHold = currentDashHold;
}

void Player::UpdateNormal()
{
    m_vec.y -= GRAVITY;

    float inputX = 0;
    if (HOLD(CInput::eRight)) inputX = 1;
    if (HOLD(CInput::eLeft)) inputX = -1;

    if (inputX != 0) {
        m_vec.x = inputX * m_speed;
        m_flip = (inputX > 0);
    }
    else {
        m_vec.x *= 0.8f;
        if (abs(m_vec.x) < 0.1f)m_vec.x = 0;
    }

    if (PUSH(CInput::eButton3)) {
        if (m_is_ground) {
            m_vec.y = m_jumpPower;
            m_isJumpTrigger = false;
        }
        else if(m_is_wall){
            m_vec.y = m_jumpPower;
            m_vec.x = -m_wallDir * WALL_JUMP_X;
            m_isJumpTrigger = false;
        }
    }

    if (m_isDashTrigger && m_canDash) {
        float dx = 0, dy = 0;
        if (HOLD(CInput::eRight)) dx = 1;
        if (HOLD(CInput::eLeft))  dx = -1;
        if (HOLD(CInput::eUp))    dy = 1; 
        if (HOLD(CInput::eDown))  dy = -1;
        if (dx == 0 && dy == 0) dx = m_flip ? 1.0f : -1.0f;
        float len = sqrt(dx * dx + dy * dy);
        if (len > 0) { dx /= len; dy /= len; }

        m_dashDir = CVector2D(dx, dy);
        m_state = PlayerState::Dash;
        m_dashTimer = m_dashMaxTime;
        m_canDash = false;

        m_isDashTrigger = false;
    }

    if (HOLD(CInput::eButton1) && m_is_wall && !m_is_ground) {
        m_state = PlayerState::Climb;
        m_vec = CVector2D(0, 0);
    }
}

void Player::UpdateDash()
{
    m_vec = m_dashDir * m_dashSpeed;
    m_dashTimer--;
    if (m_dashTimer <= 0) {
        m_state = PlayerState::Normal;
        m_vec = m_vec * 0.5f;
    }
}

void Player::UpdateClimb()
{
    m_vec.x = 0; m_vec.y = 0;
    if (HOLD(CInput::eUp))    m_vec.y = m_climbSpeed;
    if (HOLD(CInput::eDown)) m_vec.y = -m_climbSpeed;

    if (m_isJumpTrigger) {
        m_state = PlayerState::Normal;
        m_vec.y = m_jumpPower;
        m_vec.x = -m_wallDir * WALL_JUMP_X;
        m_isJumpTrigger = false;
        return;
    }

    if (!HOLD(CInput::eButton1) || !m_is_wall || m_is_ground) {
        m_state = PlayerState::Normal;
    }
}

void Player::Draw()
{

}


void Player::Collision(Base* b)
{

}