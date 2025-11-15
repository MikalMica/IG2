#include "GameScene.h"
#include "Hero.h"
#include "Laberinth.h"
#include "ComplexEnemy.h"
#include "SinbadExample.h"

void 
GameScene::loadScene() {

    mStageLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "GameInfo", "Stage: 1", 400.0);
    mInfoText = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "Info", "Game Info here!", Ogre::Real(400), Ogre::Real(200));

    mInfoText->appendText("lives = 3\n");
    mInfoText->appendText("points = 0");

    auto m_node = mSM->getRootSceneNode()->createChildSceneNode("laberinth");
    auto h_node = mSM->getRootSceneNode()->createChildSceneNode("hero");
    mHero = new Hero(Vector3(0, 0, 0), h_node, mSM);
    mLaberinth = new Laberinth(Vector3(0, 0, 0), m_node, mSM, mHero, mInfoText);
    mHero->setLaberinth(mLaberinth);
    mLaberinth->GenerateLaberinth("stage1");
    mStageLabel->setCaption("stage1");
    context->addInputListener(mHero);

    auto enemies = mLaberinth->getEnemies();

    for (auto enemy : enemies) {
        context->addInputListener(enemy);
    }
}

void 
GameScene::unloadScene() {

    delete mLaberinth; mLaberinth = nullptr;
    delete mHero; mHero = nullptr;
}