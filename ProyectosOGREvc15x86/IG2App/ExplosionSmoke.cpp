#include "ExplosionSmoke.h"
#include "OgreParticleSystem.h"
ExplosionSmoke::ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Ogre::String name): IG2Object(initPos, node, sceneMng) {
	ParticleSystem* pSys = mSM->createParticleSystem(name, "Examples/Smoke");
	node->attachObject(pSys);
}