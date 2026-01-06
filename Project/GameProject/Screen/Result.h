#pragma once
#include "Base/Base.h"

class Result : public Base {
private:
    CImage m_img;
    CImage m_clogo;
    CImage m_pclogo;
    CImage m_cimg;
    CImage m_hcimg;

    CFont m_font;
    bool m_clear;

public:
    Result(bool clear);
    void Draw() override;
    void Update() override;
};
