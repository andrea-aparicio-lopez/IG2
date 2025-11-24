#include "ExplosionSmoke.h"
#include "OgreParticleSystem.h"
#include "Constants.h"

ExplosionSmoke::ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Ogre::String name)
	: IG2Object(initPos, node, sceneMng) 
{
	ParticleSystem* pSys = mSM->createParticleSystem(name, "Examples/Smoke");
	node->attachObject(pSys);

	_timer.reset();
}

void ExplosionSmoke::frameRendered(const Ogre::FrameEvent& evt) {
	if (_timer.getMilliseconds() > cte::SMOKE_DURATION) {
		// TODO: Desaparecer
	}
}