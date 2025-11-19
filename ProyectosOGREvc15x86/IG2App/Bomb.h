#pragma once
#include "IG2Object.h"

namespace Ogre {
	class Timer;
}

class Bomb: public IG2Object
{
public:
	Bomb(Vector3 position, SceneNode* node, SceneManager* sM);
	~Bomb();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

protected:
	IG2Object* _fuse;

	Ogre::Timer* _timer;
};

