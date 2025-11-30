#include "Player.h"

Player::Player(const CVector2D& pos, bool flip) :Base(eType_Player) {

}

void Player::Draw() {
	m_img.Draw();
	
}

void Player::Update() {

}

void Player::Collision(Base* b) {

}

void Player::StateIdle()
{
}

void Player::StateRun()
{
}

void Player::StateDash()
{
}

void Player::StateGrab()
{
}

void Player::StateDown()
{
}

