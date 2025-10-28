#include "IG2App.h"
#include "IG2Object.h"
#include "Labyrinth.h"
#include "Wall.h"
#include "Hero.h"
#include "Villain.h"
#include "MegaVillain.h"
#include <OgreBitesConfigDialog.h>
#include <cmath>
#include "Constants.h"
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
    for (auto v : mVillains)
        delete v;
    delete mHero;
    delete mLabyrinth;

    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete light; light = nullptr;
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


 

    //------------------------------------------------------------------------
    // Creating Sinbad, UI and enemies

    mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "nombre", "Stage 1", 300);
    auto heroAttributesDisplay = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "nombre2", "Game Info here!", 300, 200);

   auto mLabyrinthNode = mSM->getRootSceneNode()->createChildSceneNode("labyrinth");
   mLabyrinth = new Labyrinth("../Labyrinths/stage1.txt", mLabyrinthNode, mSM);


   auto camPos = mLabyrinth->getLabyrinthSize();
   camPos *= cte::SCALE_CUBE;
   camPos /= 2;

   mCamNode->setPosition(Vector3( camPos.x, cte::CAM_Y_POS, camPos.y));
   

   Ogre::SceneNode * sinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
   Vector3 sinbadPos(mLabyrinth->getHeroPos());
   sinbadPos *= cte::SCALE_CUBE;
   mHero = new Hero(sinbadPos, sinbadNode, mSM, mLabyrinth, heroAttributesDisplay);

   addInputListener(mHero);

   std::vector<Vector3> villainPos = mLabyrinth->getVillainPos();
   for (auto p : villainPos) {
       Ogre::SceneNode* villainNode = mSM->getRootSceneNode()->createChildSceneNode();
       Villain* villain = new Villain(p * cte::SCALE_CUBE, villainNode, mSM, mLabyrinth);
       mVillains.push_back(villain);

       addInputListener(villain);
   }

   villainPos = mLabyrinth->getMegaVillainPos();
   for (auto p : villainPos) {
       Ogre::SceneNode* villainNode = mSM->getRootSceneNode()->createChildSceneNode();
       Villain* villain = new MegaVillain(p * cte::SCALE_CUBE, villainNode, mSM, mLabyrinth);
       mVillains.push_back(villain);

       addInputListener(villain);
   }



   //------------------------------------------------------------------------
   // Creating the light

   mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));


   auto lightType = mLabyrinth->getLightType();

   if (lightType == "directional") {
       Light* luz = mSM->createLight("Luz");
       luz->setType(Ogre::Light::LT_DIRECTIONAL);
       luz->setDiffuseColour(0.75, 0.75, 0.75);

       mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
       mLightNode->attachObject(luz);
       mLightNode->setDirection(Ogre::Vector3(-1, -1, -1));
   }
   else if (lightType == "point") {
       Light* luz = mSM->createLight("Luz");
       luz->setType(Ogre::Light::LT_POINT);
       luz->setDiffuseColour(0.75, 0.75, 0.75);
       luz->setAttenuation(350, 0.5, 0.005, 0.0);

       mLightNode = sinbadNode->createChildSceneNode("nLuz");
       mLightNode->setInheritScale(false);
       mLightNode->setScale(0,0,0);
       mLightNode->attachObject(luz);
   }
   else if (lightType == "spotlight") {
       Light* luz = mSM->createLight("Luz");
       luz->setType(Ogre::Light::LT_SPOTLIGHT);
       luz->setDiffuseColour(0.9f, 0.9f, 0.9f);
       luz->setSpotlightRange(Ogre::Degree(10.0f), Ogre::Degree(12.f), 0.5f);

       mLightNode = sinbadNode->createChildSceneNode("nLuz");
       mLightNode->attachObject(luz);
       mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
       mLightNode->setPosition(Vector3(0, 200, 0));
   }

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