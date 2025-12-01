#include "GameScene.h"
#include "SceneSystem.h"
#include "Labyrinth.h"
#include "Wall.h"
#include "Character.h"
#include "Hero.h"
#include "Villain.h"
#include "MegaVillain.h"
#include "Bomb.h"
#include "ExplosionSmoke.h"
#include "Constants.h"

#include <OgreLight.h>
#include <OgreTrays.h>
#include <OgreApplicationContext.h>

using namespace Ogre;

GameScene::GameScene(SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, OgreBites::ApplicationContext* appContext, std::string path)
    : Scene(root, sys, textBox) 
    , _particleSystemNameGen("ParticleSystem")
    , _bombPool(BombPool(root->createChildSceneNode(), this, sys->getSceneManager()))
{

    //--------------- LABYRINTH, SINBAD AND ENEMIES ---------------------

    auto mLabyrinthNode = _root->createChildSceneNode("labyrinth");
    mLabyrinth = new Labyrinth(path, mLabyrinthNode, _sys->getSceneManager());


    Ogre::SceneNode* sinbadNode = mLabyrinthNode->createChildSceneNode("nSinbad");
    Vector3 sinbadPos(mLabyrinth->getHeroPos());
    sinbadPos *= cte::SCALE_CUBE;
    mHero = new Hero(sinbadPos, sinbadNode, _sys->getSceneManager(), mLabyrinth, this);

    std::vector<Vector3> villainPos = mLabyrinth->getVillainPos();
    for (auto p : villainPos) {
        Ogre::SceneNode* villainNode = mLabyrinthNode->createChildSceneNode();
        Villain* villain = new Villain(p * cte::SCALE_CUBE, villainNode, _sys->getSceneManager(), mLabyrinth);
        mVillains.push_back(villain);
    }

    villainPos = mLabyrinth->getMegaVillainPos();
    for (auto p : villainPos) {
        Ogre::SceneNode* villainNode = mLabyrinthNode->createChildSceneNode();
        Villain* villain = new MegaVillain(p * cte::SCALE_CUBE, villainNode, _sys->getSceneManager(), mLabyrinth);
        mVillains.push_back(villain);
    }

    _smokePool = new SmokePool(_root->createChildSceneNode(), _sys->getSceneManager(), mLabyrinth);


    //--------------------- SKY -----------------------------
    Ogre::MeshManager::getSingleton().createPlane("mSky",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        cte::SKY_SIZE, cte::SKY_SIZE, 1, 1,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

    mSky = new IG2Object(Vector3(0, -300,0), _root->createChildSceneNode(), _sys->getSceneManager(), "mSky");

    mSky->setMaterialName("SkyMaterial");



    //--------------------- LIGHT -----------------------------


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

    delete mHero;
    delete mLabyrinth;
    delete mSky;
    for (auto v : mVillains)
        delete v;

    delete _smokePool;

    Scene::~Scene();
}

void GameScene::openScene() {

    auto camPos = mLabyrinth->getLabyrinthSize();
    camPos *= cte::SCALE_CUBE;
    camPos /= 2;

    auto cam = _sys->getSceneManager()->getSceneNode("nCam");
    cam->setPosition(Vector3(camPos.x, cte::CAM_Y_POS, camPos.y));
    //cam->lookAt(Vector3(0, -1, 0), Ogre::Node::TS_WORLD);
    cam->setDirection(Vector3(0, -1, 0), Ogre::Node::TS_WORLD);
    cam->roll(Degree(180.f));

    //TEXTBOX
    _textBox->setText("Lives: " + std::to_string(mHero->health()) +
        "\nScore: " + std::to_string(mHero->score()));

    // AÑADIR LISTENERS
    addInputListeners();

}

void GameScene::closeScene() {
    removeInputListeners();
}

void GameScene::onFrameRendered(const Ogre::FrameEvent& evt) {
    calculateCollisions();
}

void GameScene::addInputListeners() {
    _sys->addInputListener(mHero);

    for (auto villain : mVillains)
        _sys->addInputListener(villain);

    _sys->addInputListener(&_bombPool);
    _sys->addInputListener(_smokePool);
}

void GameScene::removeInputListeners() {
    _sys->removeInputListener(mHero);

    for (auto villain : mVillains)
        _sys->removeInputListener(villain);

    _sys->removeInputListener(&_bombPool);
    _sys->removeInputListener(_smokePool);
}

void GameScene::calculateCollisions() {
    for (auto villain : mVillains) {
        if (!villain->isDead() && mHero->getAABB().intersects(villain->getAABB())) {
            mHero->damageHero();
            setText();
            break;
        }
    }
}

void GameScene::placeBomb(Vector3 pos) {
    _bombPool.placeBomb(pos);
}

void GameScene::explodeBomb(Vector3 pos) {
    _smokePool->placeAllSmokes(pos);
    calculateBombCollisions(pos);
}

bool GameScene::checkCharacterBombDamage(Vector3 bombPos, Character* ch) {
    bombPos /= cte::SCALE_CUBE;
    Vector3 charPos = ch->getPosition() / cte::SCALE_CUBE;
    charPos = { floor(charPos.x), floor(charPos.y), floor(charPos.z) };

        bool collides = false;
        bool wallFound = false;

        if (bombPos.x == charPos.x) {
            if (bombPos.z <= charPos.z && (charPos.z - bombPos.z < cte::BOMB_EXPLODING_LENGTH)) {
                for (int i = 0; i < cte::BOMB_EXPLODING_LENGTH && !wallFound; ++i) {
                    wallFound = mLabyrinth->isWall({ bombPos.x, bombPos.y, bombPos.z + i });
                }
                collides = !wallFound;
            }
            else if (bombPos.z > charPos.z && (bombPos.z - charPos.z < cte::BOMB_EXPLODING_LENGTH)) {
                for (int i = -1; i < -cte::BOMB_EXPLODING_LENGTH && !wallFound; --i) {
                    wallFound = mLabyrinth->isWall({ bombPos.x, bombPos.y, bombPos.z +i});
                }
                collides = !wallFound;
            }
        }
        else if (bombPos.z == charPos.z) {
            if (bombPos.x <= charPos.x && (charPos.x - bombPos.x < cte::BOMB_EXPLODING_LENGTH)) {
                for (int i = 0; i < cte::BOMB_EXPLODING_LENGTH && !wallFound; ++i) {
                    wallFound = mLabyrinth->isWall({ bombPos.x + i, bombPos.y, bombPos.z});
                }
                collides = !wallFound;
            }
            else if (bombPos.x > charPos.x && (bombPos.x - charPos.x < cte::BOMB_EXPLODING_LENGTH)) {
                for (int i = -1; i < -cte::BOMB_EXPLODING_LENGTH && !wallFound; --i) {
                    wallFound = mLabyrinth->isWall({ bombPos.x + i, bombPos.y, bombPos.z });
                }
                collides = !wallFound;
            }
        }

        return collides;
}

void GameScene::calculateBombCollisions(Vector3 pos) {

    for (auto v : mVillains) {
        if (v->isDead()) continue;
        if (checkCharacterBombDamage(pos, v)) {
            v->damageVillain();
            _sys->removeInputListener(v);
            mHero->addScore();
            setText();
        }
    }

    if (checkCharacterBombDamage(pos, mHero)) {
        mHero->damageHero();
        setText();
    }
}

void GameScene::setText() {
    if (mHero->health() <= 0) {
        _textBox->setText("YOU LOSE");
    }
    else if (mHero->score() >= mVillains.size()) {
        _textBox->setText("YOU WIN");
    }
    else {
        _textBox->setText("Lives: " + std::to_string(mHero->health()) +
            "\nScore: " + std::to_string(mHero->score()));
    }
}