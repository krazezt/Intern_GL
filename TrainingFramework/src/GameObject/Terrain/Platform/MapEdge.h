#pragma once
#include "Terrain/StaticTerrain.h"

enum class EdgeSide {
	TOP,
	LEFT,
	BOTTOM,
	RIGHT,
};

class MapEdge : public StaticTerrain{
public:
	MapEdge();
	~MapEdge();

	void init(float x_location, float y_location) override;
	void init(EdgeSide side);
	void initCollisionBox(float x_location, float y_location, float width, float height);
	void setLocation(float x_location, float y_location);
};