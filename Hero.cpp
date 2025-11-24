#include "Hero.h"
#include "Laberinth.h"
#include "BombPooler.h"
#include "Bomb.h"

bool
Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {
	Vector2 new_direction(0, 0);

	if (evt.keysym.sym == SDLK_UP) new_direction.y = -1;
	else if (evt.keysym.sym == SDLK_DOWN) new_direction.y = 1;
	else if (evt.keysym.sym == SDLK_RIGHT) new_direction.x = 1;
	else if (evt.keysym.sym == SDLK_LEFT) new_direction.x = -1;
	direction_buffer = new_direction;

	if (evt.keysym.sym == SDLK_SPACE) placeBomb();

	return true;
}

void 
Hero::frameRendered(const Ogre::FrameEvent& evt) {
	AliveEntity::frameRendered(evt);

	if (laberinth->checkCollisions(*this, true)) {
		GetDamage();
	}
}

void Hero::GetDamage()
{
	lives--;
	resetPos();
	direction = direction_buffer = { 0, 0 };
	if (lives <= 0) {
		lives = 3;
		points = 0;
		laberinth->resetGame();
	}
	laberinth->updateInfoText();
}

void Hero::placeBomb() {
	Bomb* returned_bomb = bomb_pooler->GetBomb();
	if(returned_bomb != nullptr) 
	{
		returned_bomb->setPosition(getPosition());
		returned_bomb->ActivateBomb();
	}
}