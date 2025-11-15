#include "IntroScene.h"
#include "SceneSystem.h"
#include "Constants.h"
#include "AnimCharacter.h"

#include <OgreMath.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreApplicationContext.h>

using namespace Ogre;

IntroScene::IntroScene(SceneNode* root, SceneSystem* sys, OgreBites::TextBox* textBox, OgreBites::ApplicationContext* appContext)
	: Scene(root, sys)
{
	textBox->setText("Press S to start game");

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

	_root->_update(true, true);
	auto s = _sinbad->getAABB().getSize();
	s = cte::SCALE_HERO / s;
	_sinbad->setScale(s);

	appContext->addInputListener(_sinbad);

}

IntroScene::~IntroScene() {
	Scene::~Scene();
}

void IntroScene::openScene() {
	_sys->getSceneManager()->getSceneNode("nCam")->setPosition(Vector3(0,100,500));
	_sys->getSceneManager()->getSceneNode("nCam")->lookAt(Vector3(0, 1, -0.2), Ogre::Node::TS_LOCAL);

	startAnimation();
}

void IntroScene::closeScene() {
	
}

void IntroScene::onFrameRendered() {

}

void IntroScene::startAnimation() {
	AnimationState* sinbadDance = _sinbad->getAnimationState("Dance");
	sinbadDance->setEnabled(true);
	sinbadDance->setLoop(true);
}