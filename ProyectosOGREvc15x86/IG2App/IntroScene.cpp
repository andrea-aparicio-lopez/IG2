#include "IntroScene.h"
#include "SceneSystem.h"
#include "Constants.h"
#include "AnimCharacter.h"

#include <OgreMath.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreApplicationContext.h>
#include <OgreTimer.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

using namespace Ogre;

IntroScene::IntroScene(SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, OgreBites::ApplicationContext* appContext)
	: Scene(root, sys, textBox)
	, _timer(new Ogre::Timer())
{

	// SUELO
	Ogre::MeshManager::getSingleton().createPlane("introPlane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		3000, 1500, 1, 1,
		true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	_plane = new IG2Object(Vector3(0,0,0), _root->createChildSceneNode(), _sys->getSceneManager(), "introPlane");
	_plane->setMaterialName(FLOORMAT);


	// ------- SINBAD ---------
	_sinbad = new AnimCharacter(SINBAD_START_POS, _root->createChildSceneNode(), _sys->getSceneManager(), "Sinbad.mesh");

	_sinbad->getNode()->_update(true, true);
	auto s = _sinbad->getAABB().getSize();
	auto scale = Vector3(cte::SCALE_HERO / s.x, cte::SCALE_HERO / s.y, cte::SCALE_HERO/(s.z *1.5));
	_sinbad->setScale(scale);

	_sinbad->getNode()->setInitialState();

	appContext->addInputListener(_sinbad);

	// Espadas
	_swordLeft = _sys->getSceneManager()->createEntity("Sword.mesh");
	_swordRight = _sys->getSceneManager()->createEntity("Sword.mesh");


	// --------- OGREHEAD ---------
	_ogreHead = new AnimCharacter(OGREHEAD_START_POS, _root->createChildSceneNode(), _sys->getSceneManager(), "ogrehead.mesh");
	_ogreHead->yaw(Ogre::Radian(Degree(90.f)));

	_ogreHead->getNode()->_update(true, true);
	s = _ogreHead->getAABB().getSize();
	s = cte::SCALE_OGREHEAD / s;
	_ogreHead->setScale(s);

	_ogreHead->getNode()->setInitialState();

	appContext->addInputListener(_ogreHead);


	// --------- ANIMACIONES -----------
	createNodeAnimations();


	// ----------- LUX ---------------
	Light* luz = _sys->getSceneManager()->createLight();
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	luz->setCastShadows(true);

	auto lightNode = _root->createChildSceneNode();
	lightNode->attachObject(luz);
	lightNode->setDirection(Ogre::Vector3(0, -1, 0));

}

bool IntroScene::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_s) {
		_sys->changeScene(SceneSystem::GAME_SCENE);
	}

	return true;
}

IntroScene::~IntroScene() {
	Scene::~Scene();
}

void IntroScene::openScene() {
	_root->setVisible(true);
	_sys->getSceneManager()->getSceneNode("nCam")->setPosition(Vector3(0,100,500));
	_sys->getSceneManager()->getSceneNode("nCam")->lookAt(Vector3(0, 1, -0.2), Ogre::Node::TS_LOCAL);

	_textBox->setText("Press S to start game");

	startAnimation();
}

void IntroScene::closeScene() {
	_root->setVisible(false);
}

void IntroScene::onFrameRendered(const Ogre::FrameEvent& evt) {
	_animState->addTime(evt.timeSinceLastFrame);

	if (_timer->getMilliseconds() > DURATION_STEP * 1000) {
		switchSinbadAnimation();
		_timer->reset();
	}
}

void IntroScene::createNodeAnimations() {

	Animation* anim = _sys->getSceneManager()->createAnimation("IntroAnimation", DURATION);
	anim->setInterpolationMode(Ogre::Animation::IM_LINEAR);

	// --------------- SINBAD ---------------
	NodeAnimationTrack* sinbadTrack = anim->createNodeTrack(SINBAD);
	sinbadTrack->setAssociatedNode(_sinbad->getNode());


	// KF 0: Estado inicial
	TransformKeyFrame* kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 0);

	// KF 1: Sigue igual
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 1);

	// KF 2: Mirar derecha
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 1.2);
	kf->setRotation(_sinbad->getOrientation().getRotationTo(Vector3(1,0,0)));
	kf->setTranslate(Vector3::ZERO);
	//kf->setRotation(Quaternion(Degree(90.f), Vector3(0, 1, 0)));

	// KF 3: Caminar derecha
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 2);
	kf->setRotation(_sinbad->getOrientation().getRotationTo(Vector3(1,0,0)));
	kf->setTranslate(WALK_LENGHT);

	// KF 4: Mirar izquierda
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 2.2);
	kf->setRotation(_sinbad->getOrientation().getRotationTo(Vector3(-1, 0, 0)));
	kf->setTranslate(WALK_LENGHT);

	// KF 5: Caminar izquierda
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 4);
	kf->setRotation(_sinbad->getOrientation().getRotationTo(Vector3(-1, 0, 0)));
	kf->setTranslate(WALK_LENGHT * (-1));

	// KF 6: Mirar derecha
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 4.2);
	kf->setRotation(_sinbad->getOrientation().getRotationTo(Vector3(1, 0, 0)));
	kf->setTranslate(WALK_LENGHT * (-1));

	// KF 7: Caminar al centro
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 5);
	kf->setRotation(_sinbad->getOrientation().getRotationTo(Vector3(1, 0, 0)));
	kf->setTranslate(Vector3::ZERO);

	// KF 8: Mirar delante (estado inicial)
	kf = sinbadTrack->createNodeKeyFrame(DURATION_STEP * 5.2);



	// --------------- OGEHEAD ---------------
	NodeAnimationTrack* ogreheadTrack = anim->createNodeTrack(OGREHEAD);
	ogreheadTrack->setAssociatedNode(_ogreHead->getNode());

	// KF 0: Estado inicial
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 0);

	// KF 1: Mover derecha
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 2);
	kf->setRotation(_ogreHead->getOrientation().getRotationTo(Vector3(1, 0, 0)));
	kf->setTranslate(WALK_LENGHT * 2);

	// KF 2: Mirar izquierda
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 2.2);
	kf->setRotation(_ogreHead->getOrientation().getRotationTo(Vector3(-1, 0, 0)));
	kf->setTranslate(WALK_LENGHT * 2);

	// KF 3: Mover izquierda
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 4);
	kf->setRotation(_ogreHead->getOrientation().getRotationTo(Vector3(-1, 0, 0)));
	kf->setTranslate(Vector3::ZERO);

	// KF 4: Mirar derecha
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 4.2);
	kf->setRotation(_ogreHead->getOrientation().getRotationTo(Vector3(1, 0, 0)));
	kf->setTranslate(Vector3::ZERO);

	// KF 5: Mover derecha y desaparecer
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 5);
	//kf->setRotation(_ogreHe)
	kf->setTranslate(WALK_LENGHT);
	kf->setScale(Vector3::ZERO);

	// KF 6: Estado inicial
	kf = ogreheadTrack->createNodeKeyFrame(DURATION_STEP * 5);


	_animState = _sys->getSceneManager()->createAnimationState("IntroAnimation");
	_animState->setEnabled(true);
	_animState->setLoop(true);
}

void IntroScene::startAnimation() {
	_timer->reset();
	_currentAnimState = DANCE_1;

	AnimationState* sinbadDance = _sinbad->getAnimationState("Dance");
	sinbadDance->setEnabled(true);
	sinbadDance->setLoop(true);
}

void IntroScene::switchSinbadAnimation() {
	AnimationState* anim = nullptr;

	// Switch off current animation if necessary
	switch (_currentAnimState) {
	case DANCE_1:
		anim = _sinbad->getAnimationState("Dance");
		anim->setEnabled(false);
		anim->setLoop(false);
		break;
	case RUN_RIGHT_1:
		_sinbad->getEntity()->attachObjectToBone("Handle.L", _swordLeft);
		_sinbad->getEntity()->attachObjectToBone("Handle.R", _swordRight);
		break;
	case RUN_RIGHT_2:
		anim = _sinbad->getAnimationState("RunBase");
		anim->setEnabled(false);
		anim->setLoop(false);
		anim = _sinbad->getAnimationState("RunTop");
		anim->setEnabled(false);
		anim->setLoop(false);
		_sinbad->getEntity()->detachAllObjectsFromBone();
		break;
	default:
		break;
	}

	if(++_currentAnimState == ANIM_STATE_SIZE)
		_currentAnimState = DANCE_1;


	// switch on next animation if necessary
	switch (_currentAnimState)
	{
	case DANCE_2:
		anim = _sinbad->getAnimationState("Dance");
		anim->setEnabled(true);
		anim->setLoop(true);
		break;
	case RUN_RIGHT_1:
		anim = _sinbad->getAnimationState("RunBase");
		anim->setEnabled(true);
		anim->setLoop(true);
		anim = _sinbad->getAnimationState("RunTop");
		anim->setEnabled(true);
		anim->setLoop(true);
		break;
	default:
		break;
	}


}