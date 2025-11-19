#include "Hero.h"
#include "Laberinth.h"

bool
Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {
	Vector2 new_direction(0, 0);
	if (evt.keysym.sym == SDLK_UP) new_direction.y = -1;
	else if (evt.keysym.sym == SDLK_DOWN) new_direction.y = 1;
	else if (evt.keysym.sym == SDLK_RIGHT) new_direction.x = 1;
	else if (evt.keysym.sym == SDLK_LEFT) new_direction.x = -1;
	direction_buffer = new_direction;

	return true;
}

void 
Hero::frameRendered(const Ogre::FrameEvent& evt) {
	AliveEntity::frameRendered(evt);

	if (laberinth->checkCollisions(*this, true)) {
		removeLife();
		resetPos();
		direction = direction_buffer = { 0, 0 };
		laberinth->updateInfoText();
	}
}