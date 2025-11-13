#ifndef __SINBADEXAMPLE_H__
#define __SINBADEXAMPLE_H__

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
#include <vector>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>

class SceneSystem;

class IG2App: public OgreBites::ApplicationContext, OgreBites::InputListener {

public:
    explicit IG2App() : OgreBites::ApplicationContext("SinbadExample") {};
    virtual ~IG2App() {};

protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    SceneSystem* mSceneSys;
};

#endif
