#include "ParticleInstance.h"

void ParticleInstance::Start(Vector3 pos) {
    active = true;
    mPSys->setEmitting(true);
    timer = 0;
    mNode->setPosition(pos);
}

void ParticleInstance::frameRendered(const Ogre::FrameEvent& evt) {
    if (!active) return;

    timer += evt.timeSinceLastFrame;

    if (timer >= time_to_explode) {
        mPSys->setEmitting(false);
        active = false;
    }
}
