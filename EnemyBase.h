#pragma once
#include "AliveEntity.h"
#include <vector>
//#include <map>

class EnemyBase : public AliveEntity
{
	bool directionSelected;
	bool directionChanged;
	const vector<Vector2> posible_directions = { Vector2(0,1), Vector2(1,0), Vector2(0,-1), Vector2(-1,0) };

	int getDirectionIndex(Vector2 const& dir);
public:
	EnemyBase(Vector3 pos, SceneNode* node, SceneManager* mSM, float speed, string name = "ogrehead.mesh") : AliveEntity(pos, node, mSM, name, speed), directionSelected(false), directionChanged(false)
	{
		direction = Vector2(0, 1);
	}

	virtual ~EnemyBase(){}
	void GetDamage() override {resetPos();};

	void ChooseDirection(const Ogre::FrameEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	vector<Vector2> WalkableDirs(const Ogre::FrameEvent& evt);
protected:
};