#pragma once
#include "IG2Object.h"

namespace Ogre {
	class Timer;
}

class Labyrinth;

class Bomb: public IG2Object
{
public:
	Bomb(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, Vector2 normalizedPos);
	~Bomb();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	void explodeBomb();

protected:
	IG2Object* _fuse;
	Vector2 _normalizedPos;

	Ogre::Timer* _timer;
	Labyrinth* _lab;
	SceneNode* _particlesNode;
};

