#pragma once
#include "IG2Object.h"
class Laberinth;
class SceneNode;

class Bomb : public IG2Object
{
private:
    float time_to_explode;
    float timer;
    int explosion_range;
    float explosion_duration;
    Laberinth* laberinth;
    bool exploded = true;
    SceneNode* wickNode = nullptr;

public:
    Bomb(Vector3 pos, SceneNode* node, SceneManager* mSM, Laberinth* lab, float time_exp = 3.0f, int exp_range = 2, float expDuration = 0.1f)
        : IG2Object(pos, node, mSM, "Bomb.mesh"), time_to_explode(time_exp), timer(0.0f), explosion_range(exp_range), explosion_duration(expDuration), laberinth(lab), exploded(true)
    {
        wickNode = mNode->createChildSceneNode();
		ghostHeadNode->setPosition(0, 50, 0);
        wickNode->attachObject(mSM->createEntity("cilinder.mesh"));
    }

    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    void ActivateBomb();
    bool isExploded() { return exploded; }
    bool isAvailable() { return exploded; }
};