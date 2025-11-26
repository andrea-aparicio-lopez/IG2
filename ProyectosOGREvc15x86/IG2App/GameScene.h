#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include <OgreNameGenerator.h>

namespace Ogre {
    class Light;
}

namespace OgreBites {
    class TextBox;
    class ApplicationContext;
}

class Hero;
class Villain;
class MegaVillain;
class Labyrinth;
class Bomb;
class ExplosionSmoke;

#include "BombPool.h"
#include "SmokePool.h"

class GameScene: public Scene
{
public:
	GameScene(Ogre::SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, OgreBites::ApplicationContext* appContext, std::string path = "../Labyrinths/stage1.txt");
	~GameScene();

    void openScene() override;
    void closeScene() override;

    void onFrameRendered(const Ogre::FrameEvent& evt) override;
    void addInputListeners() override;
    void removeInputListeners() override;

    //bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

    void placeBomb(Ogre::Vector3 pos);
    void explodeBomb(Ogre::Vector3 pos);

protected:
    void calculateCollisions();
    void calculateBombCollisions();

protected:

    BombPool _bombPool;
    SmokePool* _smokePool;

    Hero* mHero = nullptr;
    Labyrinth* mLabyrinth = nullptr;

    std::vector<Villain*> mVillains;

    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::NameGenerator _particleSystemNameGen;
};

