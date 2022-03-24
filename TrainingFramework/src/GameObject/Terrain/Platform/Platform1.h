#pragma once
#include "Terrain/StaticTerrain.h"

class Platform1 : public StaticTerrain {
public:
	Platform1();
	~Platform1();

	void init(float x_location, float y_location) override;
};