#pragma once
#include <queue>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class Laberinth;
class Bomb;

class BombPooler {
private:
    const static constexpr int MAX_BOMBS = 5;
    std::queue<Bomb*> bombPool;

public:
    BombPooler(Ogre::SceneManager* mSM, Laberinth* laberinth);
    ~BombPooler();

    bool GetBomb(Bomb* returned_bomb);
};