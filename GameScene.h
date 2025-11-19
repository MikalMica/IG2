#pragma once
#include "Scene.h"

class Hero;
class Laberinth;

class GameScene : public Scene
{

	OgreBites::Label* mStageLabel = nullptr;
	OgreBites::TextBox* mInfoText = nullptr;

	Hero* mHero = nullptr;
	Laberinth* mLaberinth = nullptr;

public:
	GameScene(Ogre::SceneManager* SM, SinbadExample* cont, Ogre::SceneNode* ro, OgreBites::Label* lab, OgreBites::TextBox* text);
    ~GameScene() {
        delete mLaberinth; mLaberinth = nullptr;
        delete mHero; mHero = nullptr;
    }

	void loadScene() override;
	void unloadScene() override;

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

};

