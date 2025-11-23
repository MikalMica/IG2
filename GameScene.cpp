#include "GameScene.h"
#include "Hero.h"
#include "Laberinth.h"
#include "ComplexEnemy.h"
#include "SinbadExample.h"
#include "BombPooler.h"

GameScene::GameScene(Ogre::SceneManager* SM, SinbadExample* cont, Ogre::SceneNode* ro, OgreBites::TrayManager* TM)
    : Scene(SM, cont, ro)
    , mTrayMgr(TM)
{
    mStageLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "GameInfo", "Stage: 1", 400.0);
    mInfoText = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "Info", "Game Info here!", Ogre::Real(400), Ogre::Real(200));

    mInfoText->appendText("lives = 3\n");
    mInfoText->appendText("points = 0");

    auto m_node = root->createChildSceneNode("laberinth");
    auto h_node = root->createChildSceneNode("hero");
    mHero = new Hero(Vector3(0, 0, 0), h_node, mSM);
    mLaberinth = new Laberinth(Vector3(0, 0, 0), m_node, mSM, mHero, mInfoText);
    mHero->setLaberinth(mLaberinth);
    mLaberinth->GenerateLaberinth("stage1");
    mStageLabel->setCaption("stage1");
    context->addInputListener(mHero);

    mBombPooler = new BombPooler(mSM, mLaberinth);
    mHero->setBombPooler(mBombPooler);

    auto enemies = mLaberinth->getEnemies();

    for (auto enemy : enemies) {
        context->addInputListener(enemy);
    }
}

void 
GameScene::loadScene() {

    auto camPos = mLaberinth->getLaberinthSize();
    camPos *= mLaberinth->getWallSize();
    camPos /= 2;

    mSM->getSceneNode("nCam")->setPosition(Vector3(camPos.x, 3000, camPos.y));
    mSM->getSceneNode("nCam")->lookAt(Vector3(0, -100, 0), Ogre::Node::TS_LOCAL);
    mSM->getSceneNode("nCam")->yaw(Ogre::Radian(M_PI / 2), Ogre::Node::TS_WORLD);
}

void 
GameScene::unloadScene() {

    
}