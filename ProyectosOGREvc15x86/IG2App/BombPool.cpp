#include "BombPool.h"
#include "Constants.h"
#include "GameScene.h"
#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

BombPool::BombPool(Ogre::SceneNode* node, GameScene* scene, SceneManager* sm )
	: _poolIndex(0)
	, _mSM(sm)
	, _gameScene(scene)
{
	_myBombs = std::vector<Bomb*>(cte::MAX_HERO_BOMBS);

	for (int i = 0; i < cte::MAX_HERO_BOMBS; ++i) {
		_myBombs[i] = new Bomb(Ogre::Vector3(100,0,100), node->createChildSceneNode(), sm, i);
		_myBombs[i]->deactivate();
	}
}

BombPool::~BombPool() {
	for (auto b : _myBombs) {
		delete b;
	}
}

void BombPool::placeBomb(Vector3 pos) {
	if (_poolIndex == _myBombs.size()) return;

	_myBombs[_poolIndex]->setPosition(pos);
	_myBombs[_poolIndex]->activate();
	++_poolIndex;

}

void BombPool::explodeBomb(int index) {
	auto pos = _myBombs[index]->getPosition();

	_myBombs[index]->deactivate();

	// Swap inactive for last active bomb
	Bomb* aux = _myBombs[index];
	_myBombs[index] = _myBombs[_poolIndex - 1];
	_myBombs[_poolIndex - 1] = aux;

	--_poolIndex;

	_gameScene->explodeBomb(pos);

}

void BombPool::frameRendered(const Ogre::FrameEvent& evt) {
	int i = 0;
	while (i < _poolIndex) {
		_myBombs[i]->frameRendered(evt);
		if (_myBombs[i]->getExploded())
			explodeBomb(i);
		else ++i;
	}
}