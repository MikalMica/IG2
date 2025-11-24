#include "ParticleInstance.h"
#include "SinbadExample.h"

void ParticleInstance::Start(Vector3 pos) {
    active = true;
    mPSys->setEmitting(true);
    timer = 0;
    mNode->setPosition(pos);
}

void ParticleInstance::frameRendered(const Ogre::FrameEvent& evt) {
    if (!active) return;

    timer += evt.timeSinceLastFrame;

    if (timer >= duration) {
        mPSys->setEmitting(false);
        active = false;
    }
}

ParticleInstance::ParticleInstance(Vector3 initPos, SceneNode* parent, float dur, Ogre::SceneManager* mSM, int index, SinbadExample* cunt) {
        timer = 0;
        duration = dur;
        mNode = parent->createChildSceneNode();

        mPSys = mSM->createParticleSystem("exp" + std::to_string(index), "explosion");
        mPSys->setEmitting(false);
        mNode->attachObject(mPSys);

        mNode->setPosition(initPos);
        cunt->addInputListener(this);
}