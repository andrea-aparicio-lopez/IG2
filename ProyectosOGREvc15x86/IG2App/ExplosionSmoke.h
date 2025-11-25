#pragma once
#include "IG2Object.h"
#include <OgreTimer.h>
class ExplosionSmoke: public IG2Object
{
public:
	ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Ogre::String name);
	~ExplosionSmoke();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	bool isActive() const;

protected:
	bool _active = true;
	Ogre::String _name;

	Ogre::Timer _timer;
};

