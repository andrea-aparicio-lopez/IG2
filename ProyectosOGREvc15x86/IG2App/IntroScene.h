#pragma once
#include "Scene.h"

namespace OgreBites {
    class TextBox;
}

class IntroScene : public Scene
{
public:
	IntroScene(Ogre::SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox);
	~IntroScene();

	void openScene() override;
	void closeScene() override;

	void onFrameRendered() override;

};

