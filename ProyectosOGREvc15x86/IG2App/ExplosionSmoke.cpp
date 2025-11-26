#include "ExplosionSmoke.h"
#include "OgreParticleSystem.h"
#include "Constants.h"

ExplosionSmoke::ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int index)
	: IG2Object(initPos, node, sceneMng) 
	, _name("smoke" + to_string(index))
	, _timer(new Ogre::Timer())
{
	ParticleSystem* pSys = mSM->createParticleSystem(_name, "Examples/WhiteSmoke");
	node->attachObject(pSys);
}

ExplosionSmoke::~ExplosionSmoke() {
	mSM->getParticleSystem(_name)->setEmitting(false);

	IG2Object::~IG2Object();
}

void ExplosionSmoke::frameRendered(const Ogre::FrameEvent& evt) {
	if (_active && _timer->getMilliseconds() > cte::SMOKE_DURATION) {
		_finished = true;
	}
}

bool ExplosionSmoke::getActive() const {
	return _active;
}

bool ExplosionSmoke::getFinished() const {
	return _finished;
}

void ExplosionSmoke::activate() {
	_active = true;
	mNode->setVisible(true);
	mSM->getParticleSystem(_name)->setEmitting(true);

	_finished = false;
	_timer->reset();
}

void ExplosionSmoke::deactivate() {
	_active = false;
	mNode->setVisible(false);
	mSM->getParticleSystem(_name)->setEmitting(false);
	mSM->getParticleSystem(_name)->clear();
}