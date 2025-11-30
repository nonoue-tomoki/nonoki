#include "Map.h"

Map::Map(const CVector2D& pos) :Base(eType_Map)
{
	
}

void Map::Update()
{

}

void Map::Draw()
{
	m_img.Draw();
	m_img.SetPos(m_pos);

}

void Map::Collision(Base* b)
{

}