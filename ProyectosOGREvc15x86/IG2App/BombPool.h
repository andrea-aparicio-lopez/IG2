#pragma once
#include "Bomb.h"
#include <vector>
#include <OgreFrameListener.h>

class BombPool: public OgreBites::InputListener
{
public:
	BombPool(Ogre::SceneNode* node, GameScene* scene, SceneManager* sm);
	void placeBomb(Vector3 position);
	void explodeBomb(int index);

	~BombPool();

private:

	std::vector<Bomb*> _myBombs;
	int _poolIndex;
	SceneManager* _mSM;
	int _currentBombs;
};

