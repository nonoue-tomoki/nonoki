#include "Enemy.h"

Enemy::Enemy(const CVector2D pos) :Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy", CImage);

	m_img.SetSize(60, 60);
	m_img.SetCenter(30, 60);

	m_pos_old = m_pos = pos;

	m_rect = CRect(-30, -60, 30, 0);

	m_tick = 0;
	m_movespeed = 3;
}

void Enemy::Update() {
	m_tick++;

	if (m_tick < 60) {
		m_pos.x += m_movespeed;
	}
	else if (m_tick < 90) {
		m_pos.y -= m_movespeed;
	}
	else if (m_tick < 150) {
		m_pos.x -= m_movespeed;
	}
	else if (m_tick < 180) {
		m_pos.y += m_movespeed;
	}
	else {
		m_tick = 0;
	}

}

void Enemy::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Enemy::Collision(Base* b) {

}