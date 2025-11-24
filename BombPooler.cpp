#include "BombPooler.h"
#include "Bomb.h"
#include "Laberinth.h"
#include "SinbadExample.h"
#include "IG2Object.h"

BombPooler::BombPooler(Ogre::SceneManager* mSM, Laberinth* laberinth, SinbadExample* cont) {

    for (int i = 0; i < MAX_BOMBS; ++i) 
    {
        Bomb* bomb = new Bomb(Vector3(0,0,0), laberinth->createChildSceneNode(), mSM, laberinth, i);
        cont->addInputListener(bomb);
        bombPool.push(bomb);
    }

}

BombPooler::~BombPooler() {
    while (!bombPool.empty()) {
        Bomb* bomb = bombPool.front();
        bombPool.pop();
        delete bomb;
    }
}

Bomb* BombPooler::GetBomb() {
    Bomb* returned_bomb = bombPool.front();
    if (!returned_bomb->isAvailable()) return nullptr;

    bombPool.pop();
    bombPool.push(returned_bomb);

    return returned_bomb;
}