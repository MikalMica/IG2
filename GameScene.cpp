#include "GameScene.h"
#include "Hero.h"
#include "Laberinth.h"
#include "ComplexEnemy.h"
#include "SinbadExample.h"

GameScene::GameScene(Ogre::SceneManager* SM, SinbadExample* cont, Ogre::SceneNode* ro, OgreBites::Label* lab, OgreBites::TextBox* text)
    : Scene(SM, cont, ro)
    , mStageLabel(lab)
    , mInfoText(text)
{
    Ogre::Plane plane;
    plane.d = 1000;
    plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mSM->setSkyPlane(true, plane, "SkyMat", 1500, 50, true, 1.5, 50, 50);

    auto m_node = root->createChildSceneNode("laberinth");
    auto h_node = root->createChildSceneNode("hero");
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
GameScene::loadScene() {

    //mSM->setSkyPlaneEnabled(false);

    mStageLabel->setCaption("stage1");

    mInfoText->appendText("lives = 3\n");
    mInfoText->appendText("points = 0");

    auto camPos = mLaberinth->getLaberinthSize();
    camPos *= mLaberinth->getWallSize();
    camPos /= 2;

    mSM->getSceneNode("nCam")->setPosition(Vector3(camPos.x, 3000, camPos.y));
    mSM->getSceneNode("nCam")->lookAt(Vector3(0, -100, 0), Ogre::Node::TS_LOCAL);
    mSM->getSceneNode("nCam")->yaw(Ogre::Radian(M_PI), Ogre::Node::TS_WORLD);

    mSM->setAmbientLight(ColourValue(0.25, 0.25, 0.25));
    mLaberinth->resetGame();
    mHero->setLives(3);
}

void 
GameScene::unloadScene() {
    //mSM->setSkyPlaneEnabled(false);
    
}

void
GameScene::frameRendered(const Ogre::FrameEvent& evt) {

    if (mHero->getLives() <= 0) {
        context->changeScene(0);
    }

}