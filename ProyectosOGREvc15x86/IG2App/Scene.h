#pragma once

namespace Ogre {
	class SceneNode;
	class SceneManager;
}

namespace OgreBites {
	class ApplicationContext;
}

class SceneSystem;

class Scene
{
protected:
	Scene(Ogre::SceneNode* root, SceneSystem* sys);
public:
	~Scene();

	virtual void openScene() = 0;
	virtual void closeScene() = 0;
	virtual void addInputListeners(OgreBites::ApplicationContext* appContext) = 0;

	Ogre::SceneNode* getRoot();

protected:
	Ogre::SceneNode* _root;
	SceneSystem* _sys;

};

