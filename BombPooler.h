#pragma once
#include <queue>
class SceneNode;
class SceneManager;
class Laberinth;
class Bomb;

class BombPoler {
private:
    const static constexpr int MAX_BOMBS = 5;
    std::queue<Bomb*> bombPool;
    static BombPoler* instance;

public:
    static BombPoler* GetInstance() { return instance; };

    BombPoler(SceneManager* mSM, Laberinth* laberinth);
    ~BombPoler();

    bool GetBomb(Bomb* returned_bomb);
}