#pragma once
#include "EnemyBase.h"
#include "math.h"
#include <OgreTimer.h>

class ComplexEnemy : public EnemyBase
{
	SceneNode* ghostRightNode = nullptr;
	SceneNode* ghostLeftNode = nullptr;
	SceneNode* ghostHeadNode = nullptr;
	Timer timer;
	int time; // In miliseconds
	int degreeSign;
public:
	ComplexEnemy(Vector3 pos, SceneNode* node, SceneManager* mSM, float speed, int t = 5000) 
		: EnemyBase(pos, node, mSM, speed, "athene.mesh"), timer(), time(t), degreeSign(1) {
		
		double max = std::max(calculateBoxSize().x, std::max(calculateBoxSize().y, calculateBoxSize().z));

		ghostHeadNode = mNode->createChildSceneNode();
		ghostHeadNode->setPosition(-10, 70, -20);

		for (int i = 0; i < 5; ++i) {
			auto sphere = ghostHeadNode->createChildSceneNode();
			sphere->attachObject(mSM->createEntity("sphere.mesh"));
			sphere->setPosition(20 * cos((2 * M_PI/5)*(i+1)), 0, 20 * sin((2*M_PI / 5) * (i+1)));
			sphere->setScale(max/2000, max/2000, max/2000);
		}

		ghostRightNode = mNode->createChildSceneNode();
		ghostRightNode->setPosition(30, 0, 0);

		for (int i = 0; i < 3; ++i) {
			auto sword = ghostRightNode->createChildSceneNode();
			sword->attachObject(mSM->createEntity("Sword.mesh"));
			sword->setPosition(0, 40 * cos((2 * M_PI / 3) * (i + 1)), 40 * sin((2 * M_PI / 3) * (i + 1)));
			sword->pitch(Radian((2 * M_PI / 3) * (i + 1)));
			sword->setScale(max/10, max/10, max/10);
		}

		ghostLeftNode = mNode->createChildSceneNode();
		ghostLeftNode->setPosition(-30, 0, 0);

		for (int i = 0; i < 3; ++i) {
			auto sword = ghostLeftNode->createChildSceneNode();
			sword->attachObject(mSM->createEntity("Sword.mesh"));
			sword->setPosition(0, 40 * cos((2 * M_PI / 3) * (i + 1)), 40 * sin((2 * M_PI / 3) * (i + 1)));
			sword->pitch(Radian((2 * M_PI / 3) * (i + 1)));
			sword->setScale(max/10, max/10, max/10);
		}
	}

	~ComplexEnemy() { delete ghostHeadNode; ghostHeadNode = nullptr;  delete ghostRightNode; ghostRightNode = nullptr;  delete ghostLeftNode; ghostLeftNode = nullptr; }

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
};

