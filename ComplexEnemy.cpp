#include "ComplexEnemy.h"

void
ComplexEnemy::frameRendered(const Ogre::FrameEvent& evt) {
	EnemyBase::frameRendered(evt);

	if (timer.getMilliseconds() >= time) {
		degreeSign *= -1;
		timer.reset();
	}

	ghostHeadNode->yaw(Degree(90 * degreeSign) * evt.timeSinceLastFrame);
	ghostRightNode->pitch(Degree(90 * degreeSign) * evt.timeSinceLastFrame);
	ghostLeftNode->pitch(Degree(90 * degreeSign) * evt.timeSinceLastFrame);
}