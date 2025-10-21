#include "Hero.h"
#include "Constants.h"
#include "Labyrinth.h"
#include <cmath>

Hero::Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, OgreBites::TextBox* hAD)
	: Character(position, node, sM, lab, "Sinbad.mesh"), _heroAttributesDisplay(hAD)
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = cte::SCALE_HERO / s ;
	setScale(s);

	_heroAttributesDisplay->setText("Lives: " + std::to_string(_health) +
	"\nScore: " + std::to_string(_score));
}

Hero::~Hero() {
	Character::~Character();
}

void Hero::moveCharacter(double dt) {
	// mover al heroe en función de su velocidad
	// Dejar que la lógica de moveCharacter haga su magia
	move(dir * cte::HERO_VEL * dt);
	Character::moveCharacter(dt);
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
		default:
			break;
	}
	return true;
}

void Hero::damageHero() {
	setPosition(lab->getHeroPos() * cte::SCALE_CUBE);
	_health--;

	_heroAttributesDisplay->setText("Lives: " + std::to_string(_health) +
		"\nScore: " + std::to_string(_score));
}