#include "IntroScene.h"
#include "SceneSystem.h"
#include "Constants.h"

#include <OgreMath.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>

using namespace Ogre;

IntroScene::IntroScene(SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox)
	: Scene(root, sys)
{
	textBox->setText("Press S to start game");
}

IntroScene::~IntroScene() {
	Scene::~Scene();
}

void IntroScene::openScene() {
	_sys->getSceneManager()->getSceneNode("nCam")->setPosition(Vector3(0,0,0));
	_sys->getSceneManager()->getSceneNode("nCam")->lookAt(Vector3(0, 0, -1), Ogre::Node::TS_LOCAL);
}