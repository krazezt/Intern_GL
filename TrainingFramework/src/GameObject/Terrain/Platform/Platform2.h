#pragma once
#include "Terrain/BaseTerrain.h"

class Platform2 : public BaseTerrain {
private:
public:
	Platform2();
	~Platform2();

	void init(float x_location, float y_location) override;
	void initCollisionBox(float x_location, float y_location, float width, float height);
	void setLocation(float x_location, float y_location);

	void update(float deltaTime) override;
};