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
		getEntity()->getAnimationState("RunBase")->setEnabled(true);
		getEntity()->getAnimationState("RunTop")->setEnabled(true);
	}
	inline int getLives() { return lives; }
	inline void setLives(int nLives) { lives = nLives; }
	inline int getPoints() { return points; }
	inline void removeLife() { lives--; }
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual void GetDamage() override;
	void setBombPooler(BombPooler* pooler) { bomb_pooler = pooler; };
protected:
	void placeBomb();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override; // a�adirlo a input listener

};

