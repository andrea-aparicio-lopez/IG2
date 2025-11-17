#include "Scene.h"
#include "SceneSystem.h"

#include <OgreSceneManager.h>
#include <OgreTrays.h>

using namespace Ogre;

Scene::Scene(SceneNode* root, SceneSystem* sys, OgreBites::TextBox* tB)
	: _root(root)
	, _sys(sys)
	, _textBox(tB)
{

}

Scene::~Scene() {

}

SceneNode* Scene::getRoot() {
	return _root;
}