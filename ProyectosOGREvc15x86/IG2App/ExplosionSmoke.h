#pragma once
#include "IG2Object.h"
#include <OgreTimer.h>
class ExplosionSmoke: public IG2Object
{
public:
	ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Ogre::String name);
protected:
	Ogre::Timer _timer;
};

