#include "SmokePool.h"
#include "Constants.h"
#include "Labyrinth.h"

SmokePool::SmokePool(Ogre::SceneNode* node, SceneManager* sm, Labyrinth* lab)
	: _mSM(sm)
	, _lab(lab)
	, _mySmoke(std::vector<ExplosionSmoke*>(cte::MAX_SMOKE))
{
	for (int i = 0; i < cte::MAX_SMOKE; ++i) {
		_mySmoke[i] = new ExplosionSmoke(Vector3(0, 0, 0), node->createChildSceneNode(), sm, i);
		_mySmoke[i]->deactivate();
	}
}

SmokePool::~SmokePool() {
	for (auto s : _mySmoke)
		delete s;
}

void SmokePool::placeAllSmokes(Vector3 pos) {
	Vector3 normPos = pos / cte::SCALE_CUBE;
	normPos = Vector3(floor(normPos.x), floor(normPos.y), floor(normPos.z));

	placeSmoke(normPos * cte::SCALE_CUBE);

	for (int i = normPos.x - 1; i >= normPos.x - cte::BOMB_EXPLODING_LENGTH; i--) {
		if (i < 0 || _lab->isWall(Vector3(i, 0, normPos.z))) break;
		placeSmoke({ i * cte::SCALE_CUBE, 0, normPos.z * cte::SCALE_CUBE });
	}

	for (int i = normPos.x + 1; i <= normPos.x + cte::BOMB_EXPLODING_LENGTH; i++) {
		if (i > _lab->getLabyrinthSize().x - 1 || _lab->isWall(Vector3(i, 0, normPos.z))) break;
		placeSmoke({ i * cte::SCALE_CUBE, 0, normPos.z * cte::SCALE_CUBE });
	}

	for (int i = normPos.z - 1; i >= normPos.z - cte::BOMB_EXPLODING_LENGTH; i--) {
		if (i < 0 || _lab->isWall(Vector3(normPos.x, 0, i))) break;
		placeSmoke({ normPos.x * cte::SCALE_CUBE, 0, i * cte::SCALE_CUBE});
	}

	for (int i = normPos.z + 1; i <= normPos.z + cte::BOMB_EXPLODING_LENGTH; i++) {
		if (i > _lab->getLabyrinthSize().y - 1 || _lab->isWall(Vector3(normPos.x, 0, i))) break;
		placeSmoke({ normPos.x * cte::SCALE_CUBE, 0, i * cte::SCALE_CUBE });
	}
}

void SmokePool::placeSmoke(Vector3 pos) {
	if (_poolIndex == _mySmoke.size()) return;

	_mySmoke[_poolIndex]->setPosition(pos);
	_mySmoke[_poolIndex]->activate();
	++_poolIndex;
}

void SmokePool::clearSmoke(int index) {
	_mySmoke[index]->deactivate();

	// Swap inactive for last active bomb
	ExplosionSmoke* aux = _mySmoke[index];
	_mySmoke[index] = _mySmoke[_poolIndex - 1];
	_mySmoke[_poolIndex - 1] = aux;

	--_poolIndex;
}

void SmokePool::frameRendered(const Ogre::FrameEvent& evt) {
	int i = 0;
	while (i < _poolIndex) {
		_mySmoke[i]->frameRendered(evt);
		if (_mySmoke[i]->getFinished())
			clearSmoke(i);
		else ++i;
	}
}