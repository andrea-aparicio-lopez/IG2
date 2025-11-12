#include "SceneSystem.h"
#include "Scene.h"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "GameScene.h"

using namespace Ogre;

SceneSystem::SceneSystem(SceneManager* mSM)
	: _mSM(mSM)
{
	// Creacion de escenas
	//_scenes.push_back(new IntroScene(...));
	_scenes.push_back(new GameScene(_mSM->getRootSceneNode()->createChildSceneNode(), this, nullptr));
	_scenes.push_back(new GameScene(_mSM->getRootSceneNode()->createChildSceneNode(), this, nullptr));
}

SceneSystem::~SceneSystem() {
	for (auto s : _scenes) {
		_mSM->destroySceneNode(s->getRoot());
		delete s;
	}
}

void SceneSystem::changeScene(SceneType s) {
	_scenes[_currentScene]->closeScene();
	_mSM->getRootSceneNode()->removeChild(_scenes[_currentScene]->getRoot());
	_currentScene = s;
	_mSM->getRootSceneNode()->addChild(_scenes[_currentScene]->getRoot());
	_scenes[_currentScene]->openScene();
}

Ogre::SceneManager* SceneSystem::getSceneManager() {
	return _mSM;
}