#pragma once
#include "IG2Object.h"

namespace Ogre {
	class Timer;
}

class Labyrinth;
class GameScene;

class Bomb: public IG2Object
{
public:
	Bomb(Vector3 position, SceneNode* node, SceneManager* sM, int bombIndex);
	~Bomb();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	void explodeBomb();

	Vector2 getNormalizedPos() const;
	Ogre::String getName() const;

protected:
	void createAnimations();

protected:
	IG2Object* _fuse;
	Vector2 _normalizedPos;

	Ogre::Timer* _timer;
	SceneNode* _particlesNode;
	int _bombIndex;

	bool _exploded = false;
};

