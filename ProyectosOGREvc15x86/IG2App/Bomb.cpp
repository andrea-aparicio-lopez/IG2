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
	: IG2Object(position, node, sM, "sphere.mesh")
	, _timer(new Ogre::Timer())
	, _particlesNode(node->createChildSceneNode())
	, _name("bomb" + to_string(bombIndex))
{
	mNode->_update(true, true);

	setMaterialName("Bomb");
	auto s = getAABB().getSize();
	_initScale = cte::BOMB_MAX_SIZE / s;
	setScale(_initScale);

	_fuse = new IG2Object(Vector3(0, getAABB().getSize().y/2, 0), mNode->createChildSceneNode(), mSM, "column.mesh");
	_fuse->setScale(Vector3(0.15));
	_fuse->setMaterialName("BombFuse");

	ParticleSystem* pSys = mSM->createParticleSystem(_name, "Examples/Smoke");
	_particlesNode->attachObject(pSys);
	_particlesNode->setPosition(_fuse->getPosition()*2);
	createAnimations();
}

Bomb::~Bomb() {
	delete _fuse;

	IG2Object::~IG2Object();
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
	//_bombSizeAnimState->addTime(evt.timeSinceLastEvent);
	_particleMovementAnimState->addTime(evt.timeSinceLastEvent);

	if (_timer->getMilliseconds() >= cte::BOMB_EXPLODING_TIME && !_exploded) {
		_exploded = true;
	}
}

void Bomb::activate() {
	_active = true;
	mNode->setVisible(true);
	mSM->getParticleSystem(_name)->setEmitting(true);

	setScale(_initScale);
	mNode->setInitialState();
	_bombSizeAnimState->setEnabled(true);
	_particleMovementAnimState->setEnabled(true);
	_particleMovementAnimState->setTimePosition(Ogre::Real(0));
	_exploded = false;
	_timer->reset();
}

void Bomb::deactivate() {
	_active = false;
	mNode->setVisible(false);
	mSM->getParticleSystem(_name)->setEmitting(false);
	mSM->getParticleSystem(_name)->clear();
	_bombSizeAnimState->setEnabled(false);
	_particleMovementAnimState->setEnabled(false);
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
	mNode->setInitialState();
	_particlesNode->setInitialState();

	Animation* anim = mSM->createAnimation("BombAnim_"+ _name, cte::BOMB_SIZE_ANIM_DURATION);
	anim->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	//NODE ANIMATIONS
	NodeAnimationTrack* bombScaleTrack = anim->createNodeTrack(BOMB);
	bombScaleTrack->setAssociatedNode(mNode);
	auto normalScale = mNode->getScale();
	auto halfedScale = normalScale / 2;

	TransformKeyFrame* kf = bombScaleTrack->createNodeKeyFrame(0);
	kf->setScale(normalScale);

	kf = bombScaleTrack->createNodeKeyFrame(cte::BOMB_SIZE_ANIM_DURATION * 0.5);
	kf->setScale(halfedScale);

	kf = bombScaleTrack->createNodeKeyFrame(cte::BOMB_SIZE_ANIM_DURATION * 1);
	kf->setScale(normalScale);

	//PARTICLE ANIMATIONS
	Animation* anim2 = mSM->createAnimation("BombParticleAnim_" + _name, cte::BOMB_EXPLODING_TIME/1000.);
	anim2->setInterpolationMode(Ogre::Animation::IM_LINEAR);

	NodeAnimationTrack* particleMovementTrack = anim2->createNodeTrack(PARTICLES);
	particleMovementTrack->setAssociatedNode(_particlesNode);

	kf = particleMovementTrack->createNodeKeyFrame(0);

	kf = particleMovementTrack->createNodeKeyFrame(cte::BOMB_EXPLODING_TIME/1000.);
	kf->setTranslate(-_particlesNode->getPosition());

	_bombSizeAnimState = mSM->createAnimationState("BombAnim_" + _name);
	_bombSizeAnimState->setEnabled(true);
	_bombSizeAnimState->setLoop(true);

	_particleMovementAnimState = mSM->createAnimationState("BombParticleAnim_" + _name);
	_particleMovementAnimState->setEnabled(true);
}