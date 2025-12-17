#pragma once
#include "../Base/Base.h" 
#include "Map.h" 

class AreaChange { 
public:
    static const float spawn_x;
    static const float spawn_y;

    static void CalculateNextArea(
        int current_area_id,
        int tile_id,
        const CVector2D& current_player_pos,
        int& out_next_area_id,
        CVector2D& out_next_pos
    );
};