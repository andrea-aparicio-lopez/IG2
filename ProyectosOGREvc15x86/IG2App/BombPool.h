#pragma once
#include "Bomb.h"
#include <vector>
#include <OgreFrameListener.h>

class GameScene;

class BombPool: public OgreBites::InputListener
{
public:
	BombPool(Ogre::SceneNode* node, GameScene* scene, SceneManager* sm);
	~BombPool();

	void placeBomb(Vector3 position);
	void explodeBomb(int index);

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

private:

	std::vector<Bomb*> _myBombs;
	int _poolIndex; // primera bomba libre
	SceneManager* _mSM;
	GameScene* _gameScene;
};

