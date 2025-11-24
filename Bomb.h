#pragma once
#include "IG2Object.h"
#include <OgreParticleSystem.h>
#include <OgreSceneNode.h>

class Laberinth;

using namespace Ogre;

class Bomb : public IG2Object
{
private:
    float MIN_SCALE = 0.4;
    float MAX_SCALE = 0.5;

    float time_to_explode;
    float timer;
    int explosion_range;
    float explosion_duration;
    Laberinth* laberinth;
    bool exploded = true;
    Ogre::SceneNode* wickNode = nullptr;
    Ogre::SceneNode* mPSNode = nullptr;
    Ogre::ParticleSystem* pSys = nullptr;

public:
    Bomb(Vector3 pos, Ogre::SceneNode* node, Ogre::SceneManager* mSM, Laberinth* lab, int index, float time_exp = 3.0f, int exp_range = 2, float expDuration = 0.1f)
        : IG2Object(pos, node, mSM, "sphere.mesh"), time_to_explode(time_exp), timer(0.0f), explosion_range(exp_range), explosion_duration(expDuration), laberinth(lab), exploded(true)
    {
        wickNode = mNode->createChildSceneNode();
        auto bombacuerda = new IG2Object(Vector3(0, 50, 0), wickNode, mSM, "column.mesh");
        bombacuerda->setMaterialName("fuse");
        wickNode->setScale(0.5, 0.5, 0.5);

        mPSNode = mNode->createChildSceneNode();
        pSys = mSM -> createParticleSystem("psSmoke" + std::to_string(index), "smokeParticle");
        pSys->setEmitting(false);
        mPSNode->attachObject(pSys);

        mPSNode->setPosition(0, 50, 0);
        mPSNode->setScale(Vector3(1, 0.5f, 1));
        mNode->setScale(Vector3(1, 1, 1) * MIN_SCALE);

        setMaterialName("bomb");
    }

    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    void ActivateBomb();
    bool isExploded() { return exploded; }
    bool isAvailable() { return exploded; }
};