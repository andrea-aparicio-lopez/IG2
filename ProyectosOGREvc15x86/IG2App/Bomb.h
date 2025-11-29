#pragma once
#include "IG2Object.h"

namespace Ogre {
	class Timer;
}

class Labyrinth;

class Bomb: public IG2Object
{
public:
	Bomb(Vector3 position, SceneNode* node, SceneManager* sM, int bombIndex);
	~Bomb();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void activate();
	void deactivate();

	Vector2 getNormalizedPos() const;
	bool getExploded() const;
	bool getActive() const;

protected:
	void createAnimations();

protected:
	IG2Object* _fuse;
	SceneNode* _bombNode;
	Vector2 _normalizedPos;

	Ogre::Timer* _timer;
	SceneNode* _particlesNode;
	Ogre::String _name;

	bool _exploded = true;
	bool _active;

	Ogre::Vector3 _initScale;

	enum AnimNodeTracks {
		BOMB,
		PARTICLES
	};

	Ogre::AnimationState* _bombSizeAnimState;
	Ogre::AnimationState* _particleMovementAnimState;
};

