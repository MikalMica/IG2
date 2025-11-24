#pragma once
#include "AliveEntity.h"
#include "BombPooler.h"
class Laberinth;

class Hero : public AliveEntity
{
private:
	BombPooler* bomb_pooler;
	int lives;
	int points;
public:
	Hero(Vector3 pos, Ogre::SceneNode* node, Ogre::SceneManager* mSM) : AliveEntity(pos, node, mSM, "Sinbad.mesh"), lives(3), points(0)
	{
	}
	inline int getLives() { return lives; }
	inline int getPoints() { return points; }
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual void GetDamage() override;
	void setBombPooler(BombPooler* pooler) { bomb_pooler = pooler; };
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void placeBomb();
};

