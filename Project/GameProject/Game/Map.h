#pragma once

#include "../Base/Base.h"
#include <cmath>

#define TILE_SIZE 32.0f
#define MAP_WIDTH_TILES 50  
#define MAP_HEIGHT_TILES 20

class Map : public Base 
{
public:
	Map();
	~Map() override = default;

	void Collision(Base* b) override {}

	static int GetTile(int tx, int ty);

private:
	static int s_mapData[MAP_HEIGHT_TILES][MAP_WIDTH_TILES];

	static void InitializeMapData();
};