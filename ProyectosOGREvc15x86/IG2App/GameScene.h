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
    void bombExplodes(Bomb* bomb);

protected:
    void calculateCollisions();
    void calculateBombCollisions();

protected:
    Hero* mHero = nullptr;
    Labyrinth* mLabyrinth = nullptr;

    std::vector<Villain*> mVillains;
    std::vector<Bomb*> mBombs;
    std::vector<ExplosionSmoke*> mSmoke;

    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::NameGenerator _particleSystemNameGen;
};

