#include "SceneSystem.h"
#include "Scene.h"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include "GameScene.h"

using namespace Ogre;

SceneSystem::SceneSystem(OgreBites::ApplicationContext* appContext, SceneManager* mSM, OgreBites::TrayManager* mTrayM)
	: _appContext(appContext)
	, _mSM(mSM)
	, _mTrayM(mTrayM)
{
	_mTrayM->createLabel(OgreBites::TL_BOTTOMRIGHT, "nombre", "Stage 1", 300);
	auto heroAttributesDisplay = _mTrayM->createTextBox(OgreBites::TL_BOTTOMRIGHT, "nombre2", "Game Info here!", 300, 200);

	// Creacion de escenas
	//_scenes.push_back(new IntroScene(...));
	_scenes.push_back(new GameScene(_mSM->getRootSceneNode()->createChildSceneNode(), this, heroAttributesDisplay, appContext));

	_scenes[_currentScene]->openScene();
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

void SceneSystem::frameRendered() {
	_scenes[_currentScene]->onFrameRendered();
}