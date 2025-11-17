#pragma once

#include <OgreFrameListener.h>
#include <OgreInput.h>

namespace Ogre {
	class SceneNode;
	class SceneManager;
}

namespace OgreBites {
	class ApplicationContext;
	class TextBox;
}

class SceneSystem;

class Scene: public OgreBites::InputListener
{
protected:
	Scene(Ogre::SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textbox);
public:
	~Scene();

	virtual void openScene() = 0;
	virtual void closeScene() = 0;

	Ogre::SceneNode* getRoot();

	virtual void onFrameRendered(const Ogre::FrameEvent& evt) = 0;

protected:
	Ogre::SceneNode* _root;
	SceneSystem* _sys;
	OgreBites::TextBox* _textBox;
};

