#include "Bomb.h"
#include "Laberinth.h"
#include <OgreParticleSystem.h>
#include <OgreSceneNode.h>
#include <math.h>

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
    if (exploded) return;

    timer += evt.timeSinceLastFrame;
    mPSNode->setPosition(0, 50 - 50 * timer / time_to_explode, 0);

    mNode->setScale(Vector3(1, 1, 1) * MIN_SCALE - (MAX_SCALE - MIN_SCALE) * sinf(timer));

    if (timer >= time_to_explode) {
        laberinth->ExplodeBomb(laberinth->getLaberinthPosition(Vector2(getPosition().x, getPosition().y)), explosion_range, explosion_duration);
        mNode->setVisible(false);
        pSys->setEmitting(false);
        exploded = true;
    }
}

void Bomb::ActivateBomb() {
    timer = 0.0f;
    exploded = false;
    mNode->setVisible(true);
    pSys->setEmitting(true);
    mPSNode->setPosition(0, 50, 0);
}