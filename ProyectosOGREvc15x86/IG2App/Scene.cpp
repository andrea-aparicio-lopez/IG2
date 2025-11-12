#include "Scene.h"
#include "SceneSystem.h"

#include <OgreSceneManager.h>

using namespace Ogre;

Scene::Scene(SceneNode* root, SceneSystem* sys)
	: _root(root)
	, _sys(sys)
{

}

Scene::~Scene() {

}

SceneNode* Scene::getRoot() {
	return _root;
}