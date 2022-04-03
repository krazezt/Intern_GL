#include <stdlib.h>
#include "Collidable.h"

void Collidable::applyCollision(std::shared_ptr<Collidable> collideObj) {
	if (!this->collisionBox->detectCollision(collideObj->getCollisionBox())) return;

	std::shared_ptr<CollisionInfo> collisionInfo = std::make_shared<CollisionInfo>();

	collisionInfo->collideVector = this->velocityVector - collideObj->getVelocityVector();
	collisionInfo->collideObjCategory = collideObj->getCategory();

	Vector2 tmp_collideVector = collisionInfo->collideVector;

	collisionInfo->collisionType = CollisionManager::GetInstance()->getCollisionInteractive(this->getCategory(), collideObj->getCategory());
	collisionInfo->collideDirection = (
			std::abs(tmp_collideVector.x) > std::abs(tmp_collideVector.y) ?
			(tmp_collideVector.x < 0 ? CollideDirection::LEFT : CollideDirection::RIGHT) :
			(tmp_collideVector.y < 0 ? CollideDirection::TOP : CollideDirection::BOTTOM)
			);

	this->list_CollisionInfo.push_back(collisionInfo);
}
