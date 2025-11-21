#pragma once
#include "IG2Object.h"
class Laberinth;
class SceneNode;

using namespace Ogre;

class Bomb : public IG2Object
{
private:
    float MIN_SCALE = 0.8;
    float MAX_SCALE = 1.2;

    float time_to_explode;
    float timer;
    int explosion_range;
    float explosion_duration;
    Laberinth* laberinth;
    bool exploded = true;
    Ogre::SceneNode* wickNode = nullptr;
    Ogre::SceneNode* mPSNode = nullptr;
    ParticleSystem* pSys = nullptr;

public:
    Bomb(Vector3 pos, Ogre::SceneNode* node, SceneManager* mSM, Laberinth* lab, float time_exp = 3.0f, int exp_range = 2, float expDuration = 0.1f)
        : IG2Object(pos, node, mSM, "Bomb.mesh"), time_to_explode(time_exp), timer(0.0f), explosion_range(exp_range), explosion_duration(expDuration), laberinth(lab), exploded(true)
    {
        wickNode = mNode->createChildSceneNode();
        wickNode->setPosition(0, 50, 0);
        wickNode->attachObject(mSM->createEntity("column.mesh"));

        mPSNode = mNode->createChildSceneNode();
        pSys = mSM -> createParticleSystem("psSmoke", "smoke");
        pSys->setEmitting(false);
        mPSNode->attachObject(pSys);

        mPSNode->setPosition(0, 50, 0);
    }

    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    void ActivateBomb();
    bool isExploded() { return exploded; }
    bool isAvailable() { return exploded; }
};