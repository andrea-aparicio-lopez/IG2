#include "Hero.h"
#include "Constants.h"
#include "Labyrinth.h"
#include <cmath>
#include "Bomb.h"

Hero::Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab)
	: Character(position, node, sM, lab, "Sinbad.mesh")
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = cte::SCALE_HERO / s ;
	setScale(s);
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

	new Bomb(pos, mNode->getParentSceneNode()->createChildSceneNode(), mSM);
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