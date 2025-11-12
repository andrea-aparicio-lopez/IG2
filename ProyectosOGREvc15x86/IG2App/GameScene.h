#pragma once
#include "Scene.h"
class GameScene: public Scene
{
public:
	GameScene(Ogre::SceneNode* root, SceneSystem* sys);
	~GameScene();

};

