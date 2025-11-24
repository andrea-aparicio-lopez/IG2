#include "Bomb.h"
#include "Constants.h"
#include "Labyrinth.h"
#include "ExplosionSmoke.h"
#include "GameScene.h"

#include <OgreTimer.h>
#include <OgreParticleSystem.h>

Bomb::Bomb(Vector3 position, SceneNode* node, SceneManager* sM, Vector2 normalizedPos, Ogre::String name)
	: IG2Object(position, node, sM, "sphere.mesh") 
	, _timer(new Ogre::Timer()),
	_normalizedPos(normalizedPos),
	_particlesNode(node->createChildSceneNode()),
	_name(name)
{
	mNode->_update(true, true);
	auto s = getAABB().getSize();
	s = cte::BOMB_MAX_SIZE / s;
	setScale(s);

	setMaterialName("Bomb");

	_fuse = new IG2Object(Vector3(0, getAABB().getSize().y/2, 0), mNode->createChildSceneNode(), mSM, "column.mesh");
	_fuse->setScale(Vector3(0.15));
	_fuse->setMaterialName("BombFuse");

	_timer->reset();

	ParticleSystem* pSys = mSM->createParticleSystem(name, "Examples/Smoke");
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
			a->addTime(2.5 * evt.timeSinceLastEvent);
	}

	if (_timer->getMilliseconds() >= cte::BOMB_EXPLODING_TIME && !_exploded) {
		explodeBomb();
		_exploded = true;
	}
}

void Bomb::explodeBomb() {
	_gameScene->bombExplodes(this);
}

Vector2 Bomb::getNormalizedPos() const {
	return _normalizedPos;
}

String Bomb::getName() const {
	return _name;
}