#include "BombPooler.h"
#include "Bomb.h"
#include "Laberinth.h"
#include "IG2Object.h"

BombPoler::BombPoler(SceneManager* mSM, Laberinth* laberinth) {

    if (instance == nullptr) 
    {
        instance = this;

        for (int i = 0; i < MAX_BOMBS; ++i) 
        {
            Bomb* bomb = new Bomb(Vector3(0,0,0), laberinth->createChildSceneNode(), mSM, laberinth);
            bombPool.push(bomb);
        }

    } else delete this;

}

BombPoler::~BombPoler() {
    while (!bombPool.empty()) {
        Bomb* bomb = bombPool.front();
        bombPool.pop();
        delete bomb;
    }
}

bool BombPoler::GetBomb(Bomb* returned_bomb) {
    returned_bomb = bombPool.front();
    if (!returned_bomb->isAvailable()) return false;

    bombPool.pop();
    bombPool.push(returned_bomb);

    return true;
}