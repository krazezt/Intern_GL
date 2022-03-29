#include <stdlib.h>
#include "Collidable.h"

void Collidable::applyCollision(std::shared_ptr<Collidable> collideObj) {
	if (!this->collisionBox->detectCollision(collideObj->getCollisionBox())) return;

	std::shared_ptr<CollisionInfo> collisionInfo = std::make_shared<CollisionInfo>();

	collisionInfo->collideVector = this->velocityVector - collideObj->getVelocityVector();
	collisionInfo->collideObjCategory = collideObj->getCategory();

	Vector2 tmp_collideVector = collisionInfo->collideVector;

	if (CollisionManager::GetInstance()->getCollisionInteractive(this->getCategory(), collideObj->getCategory()) == Collision::BLOCK) {
		collisionInfo->collisionType = Collision::BLOCK;
		collisionInfo->collisionDetail = (
			std::abs(tmp_collideVector.x) > std::abs(tmp_collideVector.y) ?
			(tmp_collideVector.x < 0 ? CollisionDetail::BLOCK_LEFT : CollisionDetail::BLOCK_RIGHT) :
			(tmp_collideVector.y < 0 ? CollisionDetail::BLOCK_TOP : CollisionDetail::BLOCK_BOTTOM)
			);
	}

	this->list_CollisionInfo.push_back(collisionInfo);
}
