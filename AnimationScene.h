#pragma once
#include "Scene.h"
class IG2Object;

using namespace Ogre;
using namespace std;

class AnimationScene : public Scene
{
	IG2Object* Sinbad = nullptr;
	IG2Object* OgreHead = nullptr;
	SceneNode* SinbadNode = nullptr;
	SceneNode* OgreHeadNode = nullptr;
	AnimationState* SinbadAnimState = nullptr;
	AnimationState* OgreHeadAnimState = nullptr;
	Ogre::Entity* plane = nullptr;
	Timer animTimer;

	bool swords;
	Entity* RsinbadSword = nullptr;
	Entity* LsinbadSword = nullptr;

public:
	AnimationScene(Ogre::SceneManager* SM, SinbadExample* cont, SceneNode* ro);

	~AnimationScene() {
		delete Sinbad; Sinbad = nullptr;
		delete OgreHead; OgreHead = nullptr;
		delete plane; plane = nullptr;
	}

	void loadScene() override;
	void unloadScene() override;

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	void addKeyFrame(Ogre::NodeAnimationTrack* track, Vector3 pos, Vector3 scale, Vector3 ori, double angle, double keyFrame);
	void initSinbadAnim();
	void initOgreHeadAnim();
};

