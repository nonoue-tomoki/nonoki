#pragma once
#include "Base/Base.h"

#define MAP_TIP_SIZE 60

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