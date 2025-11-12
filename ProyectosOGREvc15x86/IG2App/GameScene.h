#pragma once
#include "Scene.h"
#include <vector>
#include <string>

namespace Ogre {
    class Light;
    class TextBox;
}

class Hero;
class Villain;
class MegaVillain;
class Labyrinth;

class GameScene: public Scene
{
public:
	GameScene(Ogre::SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, std::string path = "../Labyrinths/stage1.txt");
	~GameScene();

    void openScene() override;
    void closeScene() override;

    void addInputListeners(OgreBites::ApplicationContext* appContext) override;

protected:
    Hero* mHero = nullptr;
    Labyrinth* mLabyrinth = nullptr;

    std::vector<Villain*> mVillains;
    Ogre::SceneNode* mLightNode = nullptr;
};

