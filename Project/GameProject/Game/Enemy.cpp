#include "Enemy.h"

Enemy::Enemy(const CVector2D pos) :Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy", CImage);

	m_img.SetSize(60, 60);
	m_img.SetCenter(30, 60);

	m_pos_old = m_pos = pos;

	m_rect = CRect(-30, -60, 30, 0);
}

void Enemy::Update() {

}

void Enemy::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Enemy::Collision(Base* b) {

}