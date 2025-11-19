#pragma once
#include "Scene.h"
#include <vector>
#include <string>

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

protected:
    void calculateCollisions();

protected:
    Hero* mHero = nullptr;
    Labyrinth* mLabyrinth = nullptr;

    std::vector<Villain*> mVillains;
    Ogre::SceneNode* mLightNode = nullptr;
};

