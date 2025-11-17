#pragma once
#include "Scene.h"

class Hero;
class Laberinth;
class BombPooler;

class GameScene : public Scene
{

	OgreBites::TrayManager* mTrayMgr = nullptr;

	OgreBites::Label* mStageLabel = nullptr;
	OgreBites::TextBox* mInfoText = nullptr;

	Hero* mHero = nullptr;
	Laberinth* mLaberinth = nullptr;
	BombPoler* mBombPooler = nullptr;

public:
	GameScene(Ogre::SceneManager* SM, SinbadExample* cont, Ogre::SceneNode* ro, OgreBites::TrayManager* TM);
    ~GameScene() {
        delete mLaberinth; mLaberinth = nullptr;
        delete mHero; mHero = nullptr;
		delete mBombPooler; mBombPooler = nullptr;
    }

	void loadScene() override;
	void unloadScene() override;
};

