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

	bool	detectCollision(std::shared_ptr<CollisionBox2D> box);

	float	getLocationX() { return x_location; };
	float	getLocationY() { return y_location; };
	float	getWidth() { return width; };
	float	getHeight() { return height; };
	void	setLocation(float x_location, float y_location);
};