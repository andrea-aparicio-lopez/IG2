#pragma once

#include <vector>

class Scene;

namespace Ogre {
	class SceneManager;
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
	SceneSystem(Ogre::SceneManager* mSM);
	~SceneSystem();

	void changeScene(SceneType s);

	Ogre::SceneManager* getSceneManager();

protected:
	Ogre::SceneManager* _mSM;

	std::vector<Scene*> _scenes;
	SceneType _currentScene;
};

