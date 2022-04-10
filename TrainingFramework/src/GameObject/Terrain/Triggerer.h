#pragma once
#include "Terrain/StaticTerrain.h"

class Triggerer : public StaticTerrain {
private:
	bool	isTriggered;
public:
	Triggerer();
	~Triggerer();

	void init(float x_location, float y_location) override;
	void initCollisionBox(float x_location, float y_location, float width, float height);
	void setLocation(float x_location, float y_location);
	void trigger();
	bool checkTriggered() { return isTriggered; };
};