#include "Bomb.h"
#include "Constants.h"
#include "Labyrinth.h"
#include "ExplosionSmoke.h"
#include "GameScene.h"

#include <OgreTimer.h>
#include <OgreParticleSystem.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

Bomb::Bomb(Vector3 position, SceneNode* node, SceneManager* sM, int bombIndex)
	: IG2Object(position, node, sM) 
	, _timer(new Ogre::Timer())
	, _particlesNode(node->createChildSceneNode())
	, _name("bomb" + to_string(bombIndex))
{
	mNode->_update(true, true);

	_bombNode = mNode->createChildSceneNode();
	_bomb = new IG2Object(Vector3(0, 0, 0), _bombNode, sM, "sphere.mesh");
	_bomb->setMaterialName("Bomb");
	auto s = _bomb->getAABB().getSize();
	s = cte::BOMB_MAX_SIZE / s;
	_bombNode->setScale(s);

	_fuse = new IG2Object(Vector3(0, getAABB().getSize().y/2, 0), _bombNode->createChildSceneNode(), mSM, "column.mesh");
	_fuse->setScale(Vector3(0.15));
	_fuse->setMaterialName("BombFuse");

	ParticleSystem* pSys = mSM->createParticleSystem(_name, "Examples/Smoke");
	_particlesNode->attachObject(pSys);

	createAnimations();
}

Bomb::~Bomb() {
	delete _fuse;

	IG2Object::~IG2Object();
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
	_animState->addTime(evt.timeSinceLastEvent);
	/*if (entity->_isAnimated()) {
		Ogre::EnabledAnimationStateList anims = entity->getAllAnimationStates()->getEnabledAnimationStates();
		for (auto a : anims)
			a->addTime(evt.timeSinceLastEvent);
	}
	*/

	if (!_exploded)_bomb->setPosition(Vector3(100, 0, 100));

	if (_timer->getMilliseconds() >= cte::BOMB_EXPLODING_TIME && !_exploded) {
		_exploded = true;
	}
}

void Bomb::activate() {
	_active = true;
	mNode->setVisible(true);
	mSM->getParticleSystem(_name)->setEmitting(true);

	_exploded = false;
	_timer->reset();
}

void Bomb::deactivate() {
	_active = false;
	mNode->setVisible(false);
	mSM->getParticleSystem(_name)->setEmitting(false);
	mSM->getParticleSystem(_name)->clear();
	
}

Vector2 Bomb::getNormalizedPos() const {
	return _normalizedPos;
}

bool Bomb::getExploded() const {
	return _exploded;
}

bool Bomb::getActive() const {
	return _active;
}

void Bomb::createAnimations() {
	// TODO
	//_bombNode->setInitialState();
	//_particlesNode->setInitialState();

	Animation* anim = mSM->createAnimation("BombAnim_"+ _name, cte::BOMB_SIZE_ANIM_DURATION*2);
	anim->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	//NODE ANIMATIONS
	NodeAnimationTrack* sinbadTrack = anim->createNodeTrack(BOMB);
	sinbadTrack->setAssociatedNode(_bombNode);
	auto normalScale = _bombNode->getScale();
	auto halfedScale = normalScale / 2;

	TransformKeyFrame* kf = sinbadTrack->createNodeKeyFrame(0);
	kf->setScale(normalScale);

	kf = sinbadTrack->createNodeKeyFrame(cte::BOMB_SIZE_ANIM_DURATION);
	kf->setScale(halfedScale);

	kf = sinbadTrack->createNodeKeyFrame(cte::BOMB_SIZE_ANIM_DURATION * 2);
	kf->setScale(normalScale);
	//PARTICLE ANIMATIONS

	_animState = mSM->createAnimationState("BombAnim_" + _name);
	_animState->setEnabled(true);
	_animState->setLoop(true);
}