#pragma once

#include <vector>

#include <OgreFrameListener.h>

class Scene;

namespace Ogre {
	class SceneManager;
	class FrameEvent;
}

namespace OgreBites {
	class TrayManager;
	class ApplicationContext;
}

class SceneSystem
{
public:
	enum SceneType {
		INTRO_SCENE,
		GAME_SCENE,
		NUM_SCENES
	};

public:
	SceneSystem(OgreBites::ApplicationContext* appContext, Ogre::SceneManager* mSM, OgreBites::TrayManager* mTrayM);
	~SceneSystem();

	void changeScene(SceneType s);

	Ogre::SceneManager* getSceneManager();

	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneManager* _mSM;
	OgreBites::TrayManager* _mTrayM;

	std::vector<Scene*> _scenes;
	SceneType _currentScene = INTRO_SCENE;

	OgreBites::ApplicationContext* _appContext;

};

