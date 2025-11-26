#include "Bomb.h"
#include "Constants.h"
#include "Labyrinth.h"
#include "ExplosionSmoke.h"
#include "GameScene.h"

#include <OgreTimer.h>
#include <OgreParticleSystem.h>

Bomb::Bomb(Vector3 position, SceneNode* node, SceneManager* sM, int bombIndex)
	: IG2Object(position, node, sM, "sphere.mesh") 
	, _timer(new Ogre::Timer())
	, _particlesNode(node->createChildSceneNode())
	, _name("bomb" + to_string(bombIndex))
{
	mNode->_update(true, true);
	auto s = getAABB().getSize();
	s = cte::BOMB_MAX_SIZE / s;
	setScale(s);

	setMaterialName("Bomb");

	_fuse = new IG2Object(Vector3(0, getAABB().getSize().y/2, 0), mNode->createChildSceneNode(), mSM, "column.mesh");
	_fuse->setScale(Vector3(0.15));
	_fuse->setMaterialName("BombFuse");

	ParticleSystem* pSys = mSM->createParticleSystem(_name, "Examples/Smoke");
	_particlesNode->attachObject(pSys);
}

Bomb::~Bomb() {
	delete _fuse;

	IG2Object::~IG2Object();
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
	if (entity->_isAnimated()) {
		Ogre::EnabledAnimationStateList anims = entity->getAllAnimationStates()->getEnabledAnimationStates();
		for (auto a : anims)
			a->addTime(evt.timeSinceLastEvent);
	}

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
}