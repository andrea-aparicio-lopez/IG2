#include "ExplosionSmoke.h"
#include "OgreParticleSystem.h"
#include "Constants.h"

ExplosionSmoke::ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Ogre::String name)
	: IG2Object(initPos, node, sceneMng) 
	, _name(name)
{
	ParticleSystem* pSys = mSM->createParticleSystem(name, "Examples/WhiteSmoke");
	node->attachObject(pSys);

	_timer.reset();
}

ExplosionSmoke::~ExplosionSmoke() {
	mSM->getParticleSystem(_name)->setEmitting(false);

	IG2Object::~IG2Object();
}

void ExplosionSmoke::frameRendered(const Ogre::FrameEvent& evt) {
	if (_active && _timer.getMilliseconds() > cte::SMOKE_DURATION) {
		// TODO: Desaparecer
		mNode->setVisible(false);
	}
}

bool ExplosionSmoke::isActive() const {
	return _active;
}