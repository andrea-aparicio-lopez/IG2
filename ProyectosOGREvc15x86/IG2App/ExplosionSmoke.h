#pragma once
#include "IG2Object.h"
#include <OgreTimer.h>
class ExplosionSmoke: public IG2Object
{
public:
	ExplosionSmoke(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int index);
	~ExplosionSmoke();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	bool getActive() const;
	bool getFinished() const;

	void activate();
	void deactivate();

protected:
	bool _active;
	bool _finished;

	Ogre::String _name;

	Ogre::Timer* _timer;
};

