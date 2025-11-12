#include "GameScene.h"
#include "SceneSystem.h"
#include "Labyrinth.h"
#include "Wall.h"
#include "Hero.h"
#include "Villain.h"
#include "MegaVillain.h"
#include "Constants.h"

#include <OgreLight.h>
#include <OgreTrays.h>
#include <OgreApplicationContext.h>

using namespace Ogre;

GameScene::GameScene(Ogre::SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, std::string path)
    : Scene(root, sys) 
{

    //------------------------------------------------------------------------
    // Creating Sinbad, UI and enemies

    //mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "nombre", "Stage 1", 300);
    //auto heroAttributesDisplay = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "nombre2", "Game Info here!", 300, 200);

    auto mLabyrinthNode = _root->createChildSceneNode("labyrinth");
    mLabyrinth = new Labyrinth(path, mLabyrinthNode, _sys->getSceneManager());


    Ogre::SceneNode* sinbadNode = _root->createChildSceneNode("nSinbad");
    Vector3 sinbadPos(mLabyrinth->getHeroPos());
    sinbadPos *= cte::SCALE_CUBE;
    mHero = new Hero(sinbadPos, sinbadNode, _sys->getSceneManager(), mLabyrinth, textBox);


    std::vector<Vector3> villainPos = mLabyrinth->getVillainPos();
    for (auto p : villainPos) {
        Ogre::SceneNode* villainNode = _root->createChildSceneNode();
        Villain* villain = new Villain(p * cte::SCALE_CUBE, villainNode, _sys->getSceneManager(), mLabyrinth);
        mVillains.push_back(villain);

        //addInputListener(villain);
    }

    villainPos = mLabyrinth->getMegaVillainPos();
    for (auto p : villainPos) {
        Ogre::SceneNode* villainNode = _root->createChildSceneNode();
        Villain* villain = new MegaVillain(p * cte::SCALE_CUBE, villainNode, _sys->getSceneManager(), mLabyrinth);
        mVillains.push_back(villain);

        //addInputListener(villain);
    }


    //------------------------------------------------------------------------
    // Creating the light


    auto lightType = mLabyrinth->getLightType();

    if (lightType == "directional") {
        Light* luz = _sys->getSceneManager()->createLight("Luz");
        luz->setType(Ogre::Light::LT_DIRECTIONAL);
        luz->setDiffuseColour(0.75, 0.75, 0.75);

        mLightNode = _root->createChildSceneNode("nLuz");
        mLightNode->attachObject(luz);
        mLightNode->setDirection(Ogre::Vector3(-1, -1, -1));
    }
    else if (lightType == "point") {
        Light* luz = _sys->getSceneManager()->createLight("Luz");
        luz->setType(Ogre::Light::LT_POINT);
        luz->setDiffuseColour(0.75, 0.75, 0.75);
        luz->setAttenuation(350, 0.5, 0.005, 0.0);

        mLightNode = sinbadNode->createChildSceneNode("nLuz");
        mLightNode->setInheritScale(false);
        mLightNode->setScale(0, 0, 0);
        mLightNode->attachObject(luz);
    }
    else if (lightType == "spotlight") {
        Light* luz = _sys->getSceneManager()->createLight("Luz");
        luz->setType(Ogre::Light::LT_SPOTLIGHT);
        luz->setDiffuseColour(0.9f, 0.9f, 0.9f);
        luz->setSpotlightRange(Ogre::Degree(10.0f), Ogre::Degree(12.f), 0.5f);

        mLightNode = sinbadNode->createChildSceneNode("nLuz");
        mLightNode->attachObject(luz);
        mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
        mLightNode->setPosition(Vector3(0, 200, 0));
    }
}

GameScene::~GameScene() {
    for (auto v : mVillains)
        delete v;
    delete mHero;
    delete mLabyrinth;

    Scene::~Scene();
}

void GameScene::openScene() {

    auto camPos = mLabyrinth->getLabyrinthSize();
    camPos *= cte::SCALE_CUBE;
    camPos /= 2;

    _sys->getSceneManager()->getSceneNode("nCam")->setPosition(Vector3(camPos.x, cte::CAM_Y_POS, camPos.y));
}

void GameScene::closeScene() {

}

void GameScene::addInputListeners(OgreBites::ApplicationContext* appContext) {
    appContext->addInputListener(mHero);
}