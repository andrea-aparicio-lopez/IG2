#include "Hero.h"
#include "Constants.h"
#include "Labyrinth.h"
#include <cmath>
#include <iostream>

Hero::Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab)
	: IG2Object(position, node->createChildSceneNode(), sM, "Sinbad.mesh")
	, lab(lab)
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = cte::SCALE_HERO / s ;
	setScale(s);
}

Hero::~Hero() {

}


void Hero::setNewDir(Vector3 const& nDir) {
	nextDir = nDir;
}

void Hero::moveHero(double dt) {
	// mover al heroe
	// comprobar si hay colision
	// si hay: devolver al heroe a la posición más cercana válida
	// comprobar si puede girar
	// si puede: rotar al héroe y cambiar direccion

	move(dir * cte::HERO_VEL * dt);

	Vector3 pos = getPosition();
	pos /= cte::SCALE_CUBE;
	pos = { floor(pos.x), floor(pos.y), floor(pos.z) };

	if (lab->isWall(pos)) { // si no hay pared no hace nada
		// si hay pared devolver al heroe a la posicion valida mas cercana
	}

	turnHero();
}

void Hero::turnHero() {
	if (nextDir != dir) {
		Vector3 rotPos = getPosition() / cte::SCALE_CUBE;
		rotPos = { floor(rotPos.x), floor(rotPos.y), floor(rotPos.z) };

		Vector3 orientation = getOrientation();

		if (nextDir.x == -1 && !lab->isWall(rotPos + nextDir)) { // LEFT
			// TODO: comprobación extra para ver si ha sobrepasado la pared
			Radian r = Radian(180.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
		if (nextDir.x == 1 && !lab->isWall(rotPos + nextDir)) { // RIGHT
			// TODO: comprobación extra para ver si ha sobrepasado la pared
			Radian r = Radian(0.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
		if (nextDir.z == -1 && !lab->isWall(rotPos + nextDir)) { // UP
			// TODO: comprobación extra para ver si ha sobrepasado la pared
			Radian r = Radian(90.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
		if (nextDir.z == 1 && !lab->isWall(rotPos + nextDir)) { // UP
			// TODO: comprobación extra para ver si ha sobrepasado la pared
			Radian r = Radian(270.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
	}
}

bool Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {
	switch (evt.keysym.sym) {
		case SDLK_UP:
			nextDir = { 0,0,1 };
			break;
		case SDLK_DOWN:
			nextDir = { 0,0,-1 };
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