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
	Bomb(Vector3 position, SceneNode* node, SceneManager* sM, Vector2 normalizedPos, Ogre::String name);
	~Bomb();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	void explodeBomb();

	Vector2 getNormalizedPos() const;
	Ogre::String getName() const;

protected:
	IG2Object* _fuse;
	Vector2 _normalizedPos;

	Ogre::Timer* _timer;
	SceneNode* _particlesNode;
	Ogre::String _name;

	GameScene* _gameScene;

	bool _exploded = false;
};

