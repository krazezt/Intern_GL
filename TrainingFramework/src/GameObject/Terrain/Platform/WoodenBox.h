#pragma once
#include "Terrain/StaticTerrain.h"

class WoodenBox : public StaticTerrain {
public:
	WoodenBox();
	~WoodenBox();

	void init(float x_location, float y_location) override;
	void initCollisionBox(float x_location, float y_location, float width, float height);
	void setLocation(float x_location, float y_location);
};