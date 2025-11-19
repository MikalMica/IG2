#include "Bomb.h"
#include "Laberinth.h"

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
    if (exploded) return;

    timer += evt.timeSinceLastFrame;
    if (timer >= time_to_explode) {
        laberinth->ExplodeBomb(explosion_range, explosion_duration);
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
}