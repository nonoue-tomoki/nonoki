#pragma once
#include "Base/Base.h"
#include <unordered_set>
#include <cstdint>

class Moon : public Base {
private:
    CImage m_img;

public:
    Moon(const CVector2D& pos);

    void Update() override;
    void Draw() override;

};
