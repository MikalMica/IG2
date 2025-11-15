#pragma once
#include <OgreApplicationContext.h>
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>       
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>

class SinbadExample;

class Scene : public OgreBites::InputListener
{
protected:
	Ogre::SceneManager* mSM;
	SinbadExample* context;

public:
	Scene(Ogre::SceneManager* SM, SinbadExample* cont)
		: mSM(SM)
		, context(cont)
	{}

	virtual void loadScene() = 0;
	virtual void unloadScene() = 0;
};

