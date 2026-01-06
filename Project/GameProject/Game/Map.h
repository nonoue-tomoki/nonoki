#pragma once
#include "Base/Base.h"

#define MAP_TIP_SIZE 60

enum TileId {
    TILE_EMPTY = 0,
    TILE_SOLID = 1,
    TILE_SPIKE = 2,
    TILE_ICE = 3,
    TILE_EXIT_UP = 4,
    TILE_EXIT_RIGHT = 5,
    TILE_SPRING = 6,
};

class Map : public Base {
private:
    CImage m_img;

    int m_data[19][32];
    int m_area_id;

    int m_width;
    int m_height;

public:
    Map(int area);
    ~Map() override;

    void Update() override;
    void Draw() override;
    void Collision(Base* b) override;

    int CollisionRect(const CVector2D& pos, const CRect& rect) const;

    int GetAreaID() const { return m_area_id; }
};
