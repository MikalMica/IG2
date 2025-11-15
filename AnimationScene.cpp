#include "AnimationScene.h"
#include "IG2Object.h"
#include "SinbadExample.h"

void 
AnimationScene::loadScene() {
	context->getCamera()->setPosition(0, 0, 20);
	context->getCamera()->setOrientation(Quaternion(270,0,0,1));
	mSM->setAmbientLight(ColourValue(1, 1, 1));

	SinbadNode = mSM->getRootSceneNode()->createChildSceneNode("sinbad");
	OgreHeadNode = mSM->getRootSceneNode()->createChildSceneNode("ogrehead");

	Sinbad = new IG2Object(Vector3(0, 0, 0), SinbadNode, mSM, "Sinbad.mesh");
	OgreHead = new IG2Object(Vector3(-20, 0, 0), OgreHeadNode, mSM, "ogrehead.mesh");
	RsinbadSword = mSM->createEntity("Sword.mesh");
	LsinbadSword = mSM->createEntity("Sword.mesh");
	
	Sinbad->getEntity()->getAnimationState("Dance")->setLoop(true);

	Ogre::MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Vector3::UNIT_Y, Vector3(0, 0, 0)), 1000, 1000, 100, 80, true, 1, 100, 100, Vector3::UNIT_Z);
	Ogre::Entity* plane = mSM->createEntity("floor");
	plane->setMaterialName("AnimFloorMat");
	SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
	floor->attachObject(plane);
	floor->setPosition(Vector3(0, -10, 0));
	
	AnimationStateSet* aux = Sinbad->getEntity()->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end()) {
		auto s = it->first;
		++it;
		cout << "Animation name: " << s << endl;
	}

	SkeletonInstance* skeleton = Sinbad->getEntity()->getSkeleton();
	int numBones = skeleton->getNumBones();
	for (int i = 0; i < numBones; i++) {
		cout << skeleton->getBone(i)->getName() << endl;
	}

	animTimer.reset();
	initSinbadAnim();
	initOgreHeadAnim();

}

void 
AnimationScene::unloadScene() {
	delete Sinbad; Sinbad = nullptr;
	delete OgreHead; OgreHead = nullptr;
}

void 
AnimationScene::frameRendered(const Ogre::FrameEvent& evt) {

	if (animTimer.getMilliseconds() <= 4000) {
		Sinbad->getEntity()->getAnimationState("RunBase")->setEnabled(false);
		Sinbad->getEntity()->getAnimationState("RunTop")->setEnabled(false);
		Sinbad->getEntity()->getAnimationState("Dance")->setEnabled(true);
		Sinbad->getEntity()->getAnimationState("Dance")->addTime(evt.timeSinceLastFrame);
	}
	else {
		Sinbad->getEntity()->getAnimationState("Dance")->setEnabled(false);
		Sinbad->getEntity()->getAnimationState("RunBase")->setEnabled(true);
		Sinbad->getEntity()->getAnimationState("RunTop")->setEnabled(true);
		Sinbad->getEntity()->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
		Sinbad->getEntity()->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);
	}

	if (!swords && animTimer.getMilliseconds() >= 8500) {
		Sinbad->getEntity()->attachObjectToBone("Handle.R", RsinbadSword);
		Sinbad->getEntity()->attachObjectToBone("Handle.L", LsinbadSword);
		swords = true;
	}
	else if (swords && animTimer.getMilliseconds() < 8500) {
		Sinbad->getEntity()->detachObjectFromBone(RsinbadSword);
		Sinbad->getEntity()->detachObjectFromBone(LsinbadSword);
		swords = false;
	}

	if (animTimer.getMilliseconds() > 20000) animTimer.reset();
	SinbadAnimState->addTime(evt.timeSinceLastFrame);
	OgreHeadAnimState->addTime(evt.timeSinceLastFrame);
}

void 
AnimationScene::addKeyFrame(Ogre::NodeAnimationTrack* track, Vector3 pos, Vector3 scale, Vector3 ori, double angle, double keyFrame) {
	TransformKeyFrame* kf;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(pos);
	Quaternion i = Quaternion::IDENTITY;
	i.FromAngleAxis(Radian(angle), ori);
	kf->setRotation(i);
	kf->setScale(scale);
}

void 
AnimationScene::initSinbadAnim() {
	Animation* anim = mSM->createAnimation("InitialAnimation", 20.0);
	anim->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(SinbadNode);

	// Initial frame
	addKeyFrame(track, Vector3(0, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 0, 0), 0, 0);

	// keyframe before rotation
	addKeyFrame(track, Vector3(0, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 0, 0), 0, 4);

	// rotates
	addKeyFrame(track, Vector3(0, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 1, 0), M_PI/2, 4.5);

	// runs towards the end of the screen
	addKeyFrame(track, Vector3(20, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 1, 0), M_PI / 2, 8.5);

	// rotates
	addKeyFrame(track, Vector3(20, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 1, 0), 3*M_PI / 2, 9);

	// runs towards the end of the screen
	addKeyFrame(track, Vector3(-10, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 1, 0), 3*M_PI / 2, 16);

	// rotates
	addKeyFrame(track, Vector3(-10, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 1, 0), M_PI / 2, 16.5);

	// runs towards the center
	addKeyFrame(track, Vector3(0, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 1, 0), M_PI / 2, 19);

	// rotates
	addKeyFrame(track, Vector3(0, 0, 0), Vector3::UNIT_SCALE, Vector3(0, 0, 0), 0, 20);


	SinbadAnimState = mSM->createAnimationState("InitialAnimation");
	SinbadAnimState->setEnabled(true);
	SinbadAnimState->setLoop(true);
}

void 
AnimationScene::initOgreHeadAnim() {
	Animation* anim = mSM->createAnimation("OgreInitialAnimation", 20.0);
	anim->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(OgreHeadNode);
	double baseScale = 0.15;

	//Initial frame
	addKeyFrame(track, Vector3(-20, 0, 0), Vector3(baseScale, baseScale, baseScale), Vector3(0, 1, 0), M_PI/2, 0);

	// runs towards Sinbad
	addKeyFrame(track, Vector3(10, 0, 0), Vector3(baseScale, baseScale, baseScale), Vector3(0, 1, 0), M_PI / 2, 8.5);

	// rotates
	addKeyFrame(track, Vector3(10, 0, 0), Vector3(baseScale, baseScale, baseScale), Vector3(0, 1, 0), 3 * M_PI / 2, 9);

	// runs from Sinbad
	addKeyFrame(track, Vector3(-20, 0, 0), Vector3(baseScale, baseScale, baseScale), Vector3(0, 1, 0), 3 * M_PI / 2, 16);

	// rotates
	addKeyFrame(track, Vector3(-20, 0, 0), Vector3(baseScale, baseScale, baseScale), Vector3(0, 1, 0), M_PI / 2, 16.5);

	// goes to Sinbad position and shrinks
	addKeyFrame(track, Vector3(0, 0, -5), Vector3(baseScale/5, baseScale/5, baseScale/5), Vector3(0, 1, 0), M_PI / 2, 20);

	OgreHeadAnimState = mSM->createAnimationState("OgreInitialAnimation");
	OgreHeadAnimState->setEnabled(true);
	OgreHeadAnimState->setLoop(true);
}
