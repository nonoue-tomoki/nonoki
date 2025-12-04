#pragma once
#include "Base/Base.h"

#define TILE_SIZE 60

class Map : public Base {
private:
    CImage m_img;

    static const int m_data[19][32];

    int m_width;
    int m_height;

public:
    Map();
    ~Map() override;

    void Update() override;
    void Draw() override;
    void Collision(Base* b) override;

    int CollisionRect(const CVector2D& pos, const CRect& rect) const;
};