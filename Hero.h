#pragma once
#include "AliveEntity.h"
class Laberinth;

class Hero : public AliveEntity
{
	int lives;
	int points;
public:
	Hero(Vector3 pos, SceneNode* node, SceneManager* mSM) : AliveEntity(pos, node, mSM, "Sinbad.mesh"), lives(3), points(0)
	{
	}
	inline int getLives() { return lives; }
	inline int getPoints() { return points; }
	inline void removeLife() { lives--; }
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override; // añadirlo a input listener

};

