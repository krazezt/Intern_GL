#pragma once

class BaseGameObject {
protected:
	float x_location;
	float y_location;
	Vector2	velocityVector;
public:
	virtual void	setLocation(float location_X, float location_Y) = 0;
	float			getLocationX() { return this->x_location; };
	float			getLocationY() { return this->y_location; };
	Vector2			getVelocityVector() { return this->velocityVector; };
};
