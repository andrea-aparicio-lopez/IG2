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

	void onFrameRendered(const Ogre::FrameEvent& evt) override;
	void addInputListeners() override;
	void removeInputListeners() override;

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
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
	
	enum AnimNodeTracks {
		SINBAD,
		OGREHEAD
	};

	void createNodeAnimations();
	void startAnimation();
	void switchSinbadAnimation();

	const Ogre::Vector3 SINBAD_START_POS = { 0,55,0 };
	const Ogre::Vector3 OGREHEAD_START_POS = { -350, 60, 0 };

	const Ogre::Vector3 WALK_LENGHT = { 200,0,0 };
	const Ogre::Real DURATION = 21.0;
	const Ogre::Real DURATION_STEP = DURATION / 6;

	Ogre::Timer* _timer;

	AnimationState* _animState;

protected:
	IG2Object* _plane;
	AnimCharacter* _sinbad;

	Ogre::Entity* _swordLeft;
	Ogre::Entity* _swordRight;
	AnimCharacter* _ogreHead;

	const std::string FLOORMAT = "IntroSceneFloor";

};

