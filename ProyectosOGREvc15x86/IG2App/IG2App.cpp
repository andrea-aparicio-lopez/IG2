#include "IG2App.h"
#include "IG2Object.h"
#include <OgreBitesConfigDialog.h>
#include <cmath>

#include <Ogre.h>
#include <OgreLight.h>

using namespace std;
using namespace Ogre;


bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    return true;
}


void IG2App::shutdown() {
    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;

    // do not forget to call the base 
    OgreBites::ApplicationContext::shutdown();



}

void IG2App::setup(void) {
    mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
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

void IG2App::setupScene(void) {

    //------------------------------------------------------------------------
    // Creating the camera

    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);


    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    mCamNode->setPosition(500, 3000, 500);
    mCamNode->lookAt(Vector3(0, -100, 0), Ogre::Node::TS_LOCAL);
    mCamNode->roll(Radian(Math::PI));


     mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt) {
    calculateCollisions();
}

void IG2App::calculateCollisions() {
    for (auto villain : mVillains) {
        if (mHero->getAABB().intersects(villain->getAABB())) {
            mHero->damageHero();
            break;
        }
    }
    if (mHero->health() <= 0) {
        //end game
    }
}