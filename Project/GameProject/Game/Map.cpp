#include "Map.h"
#include <string.h>
#include <math.h> 

#define MAP_ROWS (sizeof(m_data) / sizeof(m_data[0]))
#define MAP_COLS (sizeof(m_data[0]) / sizeof(m_data[0][0]))

static bool CheckRectCollision(float a_l, float a_t, float a_r, float a_b, float b_l, float b_t, float b_r, float b_b) {
    return (a_r > b_l && a_l < b_r && a_b > b_t && a_t < b_b);
}


const int Map::m_data[19][32] = {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

Map::Map() :
    Base(eType_Map) {

    m_img = COPY_RESOURCE("MapTile", CImage);
    m_img.SetSize(TILE_SIZE, TILE_SIZE);
    m_img.SetCenter(TILE_SIZE / 2, TILE_SIZE / 2);

    m_width = MAP_COLS * TILE_SIZE;
    m_height = MAP_ROWS * TILE_SIZE;

    m_pos = CVector2D(m_width / 2, m_height / 2);
    m_rect = CRect(0, 0, m_width, m_height);
}

Map::~Map() {
}

void Map::Update() {
}

void Map::Draw() {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            if (m_data[y][x] != 0) {
                CVector2D tile_pos(
                    x * TILE_SIZE + TILE_SIZE / 2,
                    y * TILE_SIZE + TILE_SIZE / 2
                );
                m_img.SetRect(48 * m_data[y][x], 0, 48 * (m_data[y][x] + 1), 48);
                m_img.SetPos(GetScreenPos(tile_pos));
                m_img.Draw();
            }
        }
    }
    DrawRect();
}

int Map::CollisionRect(const CVector2D& pos, const CRect& rect) const {

    float p_left = pos.x + rect.m_left;
    float p_top = pos.y + rect.m_top;
    float p_right = pos.x + rect.m_right;
    float p_bottom = pos.y + rect.m_bottom;

    int tile_start_x = (int)floor(p_left / TILE_SIZE);
    int tile_end_x = (int)floor((p_right - 1) / TILE_SIZE);
    int tile_start_y = (int)floor(p_top / TILE_SIZE);
    int tile_end_y = (int)floor((p_bottom - 1) / TILE_SIZE);


    for (int y = tile_start_y; y <= tile_end_y; y++) {
        for (int x = tile_start_x; x <= tile_end_x; x++) {

            if (x < 0 || x >= MAP_COLS || y < 0 || y >= MAP_ROWS) continue;

            if (m_data[y][x] != 0) {
                float t_left = x * TILE_SIZE;
                float t_top = y * TILE_SIZE;
                float t_right = (x + 1) * TILE_SIZE;
                float t_bottom = (y + 1) * TILE_SIZE;

                if (CheckRectCollision(p_left, p_top, p_right, p_bottom, t_left, t_top, t_right, t_bottom)) {
                    return m_data[y][x];
                }
            }
        }
    }

    return 0;
}


void Map::Collision(Base* b) {
}