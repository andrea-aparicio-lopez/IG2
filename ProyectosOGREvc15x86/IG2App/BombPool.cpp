#include "BombPool.h"
#include "Constants.h"
#include "GameScene.h"
#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

BombPool::BombPool(Ogre::SceneNode* node, GameScene* scene, SceneManager* sm ): _currentBombs(0), _poolIndex(0), _mSM(sm){
	_myBombs = std::vector<Bomb*>(cte::MAX_HERO_BOMBS);

	for (int i = 0; i < cte::MAX_HERO_BOMBS; i++) {
		_myBombs[i] = new Bomb(Ogre::Vector3(0,0,0), node, sm, i);
		sm->getParticleSystem(to_string(i))->setVisible(false);
		_myBombs[i]->setVisible(false);
	}
}

BombPool::~BombPool() {
	for (auto b : _myBombs) {
		delete b;
	}
}

void BombPool::placeBomb(Vector3 pos) {
	if (_currentBombs < cte::MAX_HERO_BOMBS) {
		_myBombs[_poolIndex]->setPosition(pos);
		_myBombs[_poolIndex]->setVisible(true);
		_mSM->getParticleSystem(to_string(_poolIndex))->setVisible(true);

		_poolIndex++;
		if (_poolIndex >= cte::MAX_HERO_BOMBS) _poolIndex = 0;
	}
}

void BombPool::explodeBomb(int index) {

}

