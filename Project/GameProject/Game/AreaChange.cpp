#include "AreaChange.h"
#include "Map.h"
#include <cmath>

const float AreaChange::spawn_x = (1.5f * MAP_TIP_SIZE);
const float AreaChange::spawn_y = (16.5f * MAP_TIP_SIZE);


void AreaChange::CalculateNextArea(
    int current_area_id,
    int tile_id,
    const CVector2D& current_player_pos,
    int& out_next_area_id,
    CVector2D& out_next_pos
) {
    if (tile_id != 4 && tile_id != 5) {
        out_next_area_id = current_area_id;
        out_next_pos = current_player_pos;
        return;
    }

    int X = current_area_id / 10;
    int Y = current_area_id % 10;

    if (tile_id == 4) {
        Y++;
        out_next_area_id = X * 10 + Y;
        out_next_pos = CVector2D(AreaChange::spawn_x, current_player_pos.y);
    }
    else if (tile_id == 5) {
        X++;
        out_next_area_id = X * 10 + Y;
        out_next_pos = CVector2D(current_player_pos.x, AreaChange::spawn_y);
    }
}