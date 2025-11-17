#include "AliveEntity.h"
#include "Laberinth.h"

void
AliveEntity::frameRendered(const Ogre::FrameEvent& evt) {
	Walk(evt);
}


void
AliveEntity::Walk(const Ogre::FrameEvent& evt) {
	Vector3 desired_direction = Vector3(direction_buffer.x, 0, direction_buffer.y);
	Vector3 current_direction = Vector3(direction.x, 0, direction.y);

	Vector3 desired_new_pos = mNode->getPosition() + desired_direction * (laberinth->getWallSize());
	if (can_move_to_desired) direction = direction_buffer;


	Quaternion q = this->getOrientation().getRotationTo(current_direction);
	mNode->rotate(q);

	Vector3 new_pos = mNode->getPosition() + current_direction * (laberinth->getWallSize() / 2);
	bool can_move = laberinth->isPositionWalkable(new_pos.x, new_pos.z);

	if (can_move) move(current_direction * (speed * evt.timeSinceLastFrame));

	laberinth->correctPosition(*this);
	
}