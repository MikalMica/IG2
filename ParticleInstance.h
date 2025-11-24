#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <iostream>
#include <OgreParticleSystem.h>

class SinbadExample;

using namespace Ogre;

class ParticleInstance : public OgreBites::InputListener {
public:

    ParticleInstance(Vector3 initPos, SceneNode* parent, float dur, Ogre::SceneManager* mSM, int index, SinbadExample* cunt);

    ~ParticleInstance() {
        delete mPSys;
    }

    void Start(Vector3 pos);
    virtual void frameRendered(const Ogre::FrameEvent& evt) override;
private:

    Ogre::ParticleSystem* mPSys;
    SceneNode* mNode;
    float timer = 0;
    float duration;
    bool active;
};