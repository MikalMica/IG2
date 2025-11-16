#include "SinbadExample.h"
#include "GameScene.h"
#include "AnimationScene.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace Ogre;

bool SinbadExample::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    if (evt.keysym.sym == SDLK_s) {
        if (currScene != 1)
            changeScene(1);
    }

    return true;
}


void SinbadExample::shutdown() {

    scenes[currScene]->unloadScene();

    for (auto scene : scenes) {
        delete scene;
        scene = nullptr;
    }
    
    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;

    // do not forget to call the base 
    OgreBites::ApplicationContext::shutdown();
}

void SinbadExample::setup(void) {

    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);
        
    mSM->addRenderQueueListener(mOverlaySystem);
    //mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", getRenderWindow());
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);

    addInputListener(mTrayMgr);

    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}
//hola chat.
void SinbadExample::setupScene(void) {

    //------------------------------------------------------------------------
    // Creating the camera

    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, -1500, 0);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);

    //------------------------------------------------------------------------
    // Creating Scene

    scenes.push_back(new AnimationScene(mSM, this, mSM->getRootSceneNode()->createChildSceneNode("AnimRoot")));
    scenes.push_back(new GameScene(mSM, this, mSM->getRootSceneNode()->createChildSceneNode("GameRoot"), mTrayMgr));

    for (auto scene : scenes) {
        addInputListener(scene);
        mSM->getRootSceneNode()->removeChild(scene->getRoot());
    }

    mSM->getRootSceneNode()->addChild(scenes[currScene]->getRoot());
    scenes[currScene]->loadScene();
}

void 
SinbadExample::changeScene(int nScene) {
    scenes[currScene]->unloadScene();
    mSM->getRootSceneNode()->removeChild(scenes[currScene]->getRoot());
    currScene = nScene;
    mSM->getRootSceneNode()->addChild(scenes[currScene]->getRoot());
    scenes[currScene]->loadScene();
}
