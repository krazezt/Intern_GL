#pragma once
#include "Sprite2D.h"

class CollisionBox2D {
private:
	float	x_location;
	float	y_location;
	float	width;
	float	height;

	bool	showTestBox;
	std::shared_ptr<Sprite2D>	Test_box;
public:
	CollisionBox2D();
	~CollisionBox2D();

	void	init(float x_location, float y_location, float width, float height);
	void	update(float deltaTime);
	void	draw();

	bool	detectCollision(CollisionBox2D box1, CollisionBox2D box2);
	void	setLocation(float x_location, float y_location);
};