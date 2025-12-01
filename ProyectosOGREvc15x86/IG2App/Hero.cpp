#include "Hero.h"
#include "Constants.h"
#include "Labyrinth.h"
#include <cmath>
#include "Bomb.h"
#include "GameScene.h"

Hero::Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, GameScene* scene)
	: Character(position, node, sM, lab, "Sinbad.mesh"), _gameScene(scene)
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = Vector3(cte::SCALE_HERO / s.x, cte::SCALE_HERO / s.y, cte::SCALE_HERO / (s.z * 1.5));
	setScale(s);

	startAnimation();

}

Hero::~Hero() {
	Character::~Character();
}

void Hero::moveCharacter(double dt) {
	// mover al heroe en función de su velocidad
	// Dejar que la lógica de moveCharacter haga su magia
	move(dir * cte::HERO_VEL * dt);
	Character::moveCharacter(dt);
	if(_isImmune && (_immunityTime -= dt) < 0) {
		_isImmune = false;
	}
}

bool Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {
	switch (evt.keysym.sym) {
		case SDLK_UP:
			nextDir = { 0,0,-1 };
			break;
		case SDLK_DOWN:
			nextDir = { 0,0,1 };
			break;
		case SDLK_LEFT:
			nextDir = { -1,0,0 };
			break;
		case SDLK_RIGHT:
			nextDir = { 1,0,0 };
			break;
		case SDLK_q:
			placeBomb();
			break;
		default:
			break;
	}
	return true;
}

void Hero::placeBomb() {
	Vector3 pos = getPosition() / cte::SCALE_CUBE;
	pos = Vector3(floor(pos.x), floor(pos.y), floor(pos.z));
	pos *= cte::SCALE_CUBE;

	_gameScene->placeBomb(pos);
}

void Hero::addScore() {
	_score++;
}

void Hero::damageHero() {
	if (!_isImmune && --_health) {
		resetHeroPos();

		_isImmune = true;
		_immunityTime = cte::HERO_IMMUNITY;
	}
	else if (!_health) {
		resetHeroPos();
	}
}

void Hero::resetHeroPos() {
	setPosition(lab->getHeroPos() * cte::SCALE_CUBE);
	dir = nextDir = directions[2];
	turnCharacter();
}

void Hero::startAnimation() {
	AnimationState* anim = entity->getAnimationState("RunBase");
	anim->setEnabled(true);
	anim->setLoop(true);
	anim = entity->getAnimationState("RunTop");
	anim->setEnabled(true);
	anim->setLoop(true);
}