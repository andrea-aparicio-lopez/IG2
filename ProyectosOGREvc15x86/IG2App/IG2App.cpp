#include "IG2App.h"
#include "IG2Object.h"
#include "Labyrinth.h"
#include "Wall.h"
#include "Hero.h"
#include "Villain.h"
#include "MegaVillain.h"
#include <OgreBitesConfigDialog.h>

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

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);


    //------------------------------------------------------------------------
    // Creating the light

    mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));


 

    //------------------------------------------------------------------------
    // Creating Sinbad
    /*
    Ogre::Entity* ent = mSM->createEntity("cube.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent);

    // Show bounding box
    mSinbadNode->showBoundingBox(true);

    */

    mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "nombre", "Stage 1", 300);
    auto heroAttributesDisplay = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "nombre2", "Game Info here!", 300, 200);

   mLabyrinthNode = mSM->getRootSceneNode()->createChildSceneNode("labyrinth");
   Labyrinth* lab = new Labyrinth("../Labyrinths/stage1.txt", mLabyrinthNode, mSM);


   Ogre::SceneNode * sinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
   Vector3 sinbadPos(lab->getHeroPos());
   sinbadPos *= cte::SCALE_CUBE;
   mHero = new Hero(sinbadPos, sinbadNode, mSM, lab, heroAttributesDisplay);

   addInputListener(mHero);

   std::vector<Vector3> villainPos = lab->getVillainPos();
   for (auto p : villainPos) {
       Ogre::SceneNode* villainNode = mSM->getRootSceneNode()->createChildSceneNode();
       mVillainNodes.push_back(villainNode);
       Villain* villain = new MegaVillain(p * cte::SCALE_CUBE, villainNode, mSM, lab);

       addInputListener(villain);
   }




   auto lightType = lab->getLightType();

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
       //luz->setAttenuation(500, 0.5, 0.5, 1);
       mLightNode = sinbadNode->createChildSceneNode("nLuz");
       mLightNode->attachObject(luz);
       mLightNode->setPosition(sinbadNode->getPosition() + Vector3(0,100,0));
   }
   else if (lightType == "spotlight") {
       Light* luz = mSM->createLight("Luz");
       luz->setType(Ogre::Light::LT_SPOTLIGHT);
       luz->setDiffuseColour(0.75f, 0.75f, 0.75f);
       //luz->setSpotlightRange(Ogre::Degree(40.0f), Ogre::Degree(45.f), 1.0f);
      /* luz->setDirection(Ogre::Vector3(0, -1, 0));
       luz->setPosition(sinbadPos + Ogre::Vector3(0, 400, 0));*/

       mLightNode = sinbadNode->createChildSceneNode("nLuz");
       mLightNode->attachObject(luz);
       auto pos = sinbadPos + Vector3(0, 200, 0);
       mLightNode->setPosition(pos);
       mLightNode->setDirection(Vector3(0, -1, 0));
   }



    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);

    // Set scale of Sinbad
    //mSinbadNode->setScale(20, 20, 20);

    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);   
    // 
   
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt) {
    calculateCollisions();
}

void IG2App::calculateCollisions() {
    for (auto villain : mVillainNodes) {
        if (mHero->getAABB().intersects(villain->_getWorldAABB())) {
            std::cout << "COLLISION" << '\n';
            mHero->damageHero();
            break;
        }
    }
    if (mHero->health() <= 0) {
        //end game
    }
}