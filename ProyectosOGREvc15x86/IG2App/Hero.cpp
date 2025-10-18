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

void Hero::frameRendered(const Ogre::FrameEvent& evt) {
	moveHero(evt.timeSinceLastFrame);
}

void Hero::moveHero(double dt) {
	// mover al heroe
	// comprobar si hay colision
	// si hay: devolver al heroe a la posición más cercana válida
	// comprobar si puede girar
	// si puede: rotar al héroe y cambiar direccion
	//A
	move(dir * cte::HERO_VEL * dt);

	Vector3 pos = getPosition() + Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5;
	std::cout << "Pos1: " << pos.x << " " << pos.z << '\n';
	pos /= cte::SCALE_CUBE;
	std::cout << "Pos2: " << pos.x << " " << pos.z << '\n';
	Vector3 flooredPos = { floor(pos.x), floor(pos.y), floor(pos.z) };

	Vector3 center = flooredPos + Vector3(0.5, 0, 0.5);

	bool taspasao = false;

	if (dir.z > 0 && pos.z > center.z) {
		taspasao = true;
	}
	if (dir.z < 0 && pos.z < center.z) {
		taspasao = true;
	}
	if (dir.x > 0  && pos.x > center.x) {
		taspasao = true;
	}
	if (dir.x < 0 && pos.x < center.x) {
		taspasao = true;
	}

	if (taspasao) {
		if (!lab->isWall(flooredPos + nextDir) && dir != nextDir) {
			setPosition(center * cte::SCALE_CUBE -Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5);
			dir = nextDir;
			turnHero();
		}

		if (lab->isWall(flooredPos + dir)) {
			setPosition(center * cte::SCALE_CUBE -Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5);
		}
	}
}

void Hero::turnHero() {
	Quaternion q = this->getOrientation().getRotationTo(dir);
	mNode->rotate(q);
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