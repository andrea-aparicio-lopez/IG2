#pragma once
#include "Scene.h"
#include "AnimCharacter.h"

#include <string>

namespace OgreBites {
    class TextBox;
	class ApplicationContext;
}

class IntroScene : public Scene
{
public:
	IntroScene(Ogre::SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, OgreBites::ApplicationContext* appContext);
	~IntroScene();

	void openScene() override;
	void closeScene() override;

	void onFrameRendered() override;

protected:
	enum AnimState {
		DANCE_1,
		RUN_RIGHT_1,
		RUN_LEFT_1,
		RUN_LEFT_2,
		RUN_RIGHT_2,
		DANCE_2,
		ANIM_STATE_SIZE
	};

	int _currentAnimState = DANCE_1;

	void startAnimation();
	void switchSinbadAnimation();

protected:
	IG2Object* _plane;
	AnimCharacter* _sinbad;
	//SceneNode* _sinbadNode;

	IG2Object* _swordLeft;
	IG2Object* _swordRight;
	IG2Object* _ogreHead;

	const std::string FLOORMAT = "LabyrinthFloor"; // Todo cambiar material

	// ANIMACIONES
	const Ogre::Vector3 SINBAD_START_POS = { 0,50,0 };

	Ogre::Timer* _timer;

};

