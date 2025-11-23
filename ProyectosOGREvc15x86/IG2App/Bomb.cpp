#include "Bomb.h"
#include "Constants.h"
#include "Labyrinth.h"

#include <OgreTimer.h>
#include <OgreParticleSystem.h>
#include <OgreNameGenerator.h>
#include "ExplosionSmoke.h"

Bomb::Bomb(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, Vector2 normalizedPos, Ogre::String name)
	: IG2Object(position, node, sM, "sphere.mesh") 
	, _timer(new Ogre::Timer()),
	_lab(lab),
	_normalizedPos(normalizedPos),
	_particlesNode(node->createChildSceneNode()),
	_name(name)
{
	mNode->_update(true, true);
	auto s = getAABB().getSize();
	s = cte::BOMB_MAX_SIZE / s;
	setScale(s);

	setMaterialName("Bomb");

	_fuse = new IG2Object(Vector3(0, getAABB().getSize().y/2, 0), mNode->createChildSceneNode(), mSM, "column.mesh");
	_fuse->setScale(Vector3(0.15));
	_fuse->setMaterialName("BombFuse");

	_timer->reset();

	_lab->setBomb(normalizedPos);

	ParticleSystem* pSys = mSM->createParticleSystem(name, "Examples/Smoke");
	_particlesNode->attachObject(pSys);
}

Bomb::~Bomb() {
	delete _fuse;
	IG2Object::~IG2Object();
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
	if (entity->_isAnimated()) {
		Ogre::EnabledAnimationStateList anims = entity->getAllAnimationStates()->getEnabledAnimationStates();
		for (auto a : anims)
			a->addTime(2.5 * evt.timeSinceLastEvent);
	}

	if (_timer->getMilliseconds() >= cte::BOMB_EXPLODING_TIME && !_exploded) {
		explodeBomb();
		_exploded = true;
	}
}

void Bomb::explodeBomb() {
	_lab->removeBomb(_normalizedPos);
	setVisible(false);

	//añadir las posiciones disponibles para los humos
	std::vector<Vector2> smokePositions;
	for (int i = _normalizedPos.x - 1; i >= _normalizedPos.x - cte::BOMB_EXPLODING_LENGTH; i--) {
		if (i < 0 || _lab->isWall(Vector3(i, 0, _normalizedPos.y))) break;
		smokePositions.push_back(Vector2(i, _normalizedPos.y));
	}

	for (int i = _normalizedPos.x +1; i <= _normalizedPos.x + cte::BOMB_EXPLODING_LENGTH; i++) {
		if (i > _lab->getLabyrinthSize().x -1 || _lab->isWall(Vector3(i, 0, _normalizedPos.y))) break;
		smokePositions.push_back(Vector2(i, _normalizedPos.y));
	}

	for (int i = _normalizedPos.y - 1; i < _normalizedPos.y - cte::BOMB_EXPLODING_LENGTH; i--) {
		if (i < 0 || _lab->isWall(Vector3(_normalizedPos.x, 0, i))) break;
		smokePositions.push_back(Vector2(_normalizedPos.x, i));
	}

	for (int i = _normalizedPos.y + 1; i <= _normalizedPos.y + cte::BOMB_EXPLODING_LENGTH; i++) {
		if (i > _lab->getLabyrinthSize().y - 1 || _lab->isWall(Vector3(_normalizedPos.x, 0, i))) break;
		smokePositions.push_back(Vector2(_normalizedPos.x, i));
	}

	//por cada posicion crea un humo
	for (int i = 0; i < smokePositions.size(); i++) {
		Vector2 relPos = smokePositions[i] - _normalizedPos;

		Ogre::String name = _name + "_" + to_string(i);
		new ExplosionSmoke(Vector3(relPos.x * cte::SCALE, 0, relPos.y * cte::SCALE), mNode->createChildSceneNode(),mSM ,name);
	}
}