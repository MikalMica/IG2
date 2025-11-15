#pragma once
#include "Scene.h"

class Hero;
class Laberinth;

class GameScene : public Scene
{

	OgreBites::TrayManager* mTrayMgr = nullptr;

	OgreBites::Label* mStageLabel = nullptr;
	OgreBites::TextBox* mInfoText = nullptr;

	Hero* mHero = nullptr;
	Laberinth* mLaberinth = nullptr;

public:
	GameScene(Ogre::SceneManager* SM, SinbadExample* cont, OgreBites::TrayManager* TM)
		: Scene(SM, cont)
		, mTrayMgr(TM)
	{ }

	void loadScene() override;
	void unloadScene() override;
};

