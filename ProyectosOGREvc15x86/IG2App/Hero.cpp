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
		}

		if (lab->isWall(flooredPos + dir)) {
			setPosition(center * cte::SCALE_CUBE -Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5);
		}
	}

	/*if (dir.x != 0) { // comprobacion eje x
		bool tasPasao = (getPosition().x * dir) > (center * dir);
		if (tasPasao) {
			// Comprobar si hay pared
			// Comprobar si puede girar
			// Si hay pared o puede girar, resetear posicion al centro
			if (lab->isWall(pos + dir)) {
				setPosition({ center, getPosition().y, getPosition().z });
			}
			else if (!lab->isWall(pos + nextDir)) {
				setPosition({ center, getPosition().y, getPosition().z });
				dir = nextDir;
			}
		}
	}
	else if (dir.z != 0) {
		bool tasPasao = (getPosition().z + dir) > (center * dir);
		if (tasPasao) {
			if (lab->isWall(pos + dir)) {
				setPosition({ getPosition().x, getPosition().y, center});
			}
			else if (!lab->isWall(pos + nextDir)) {
				setPosition({ getPosition().x, getPosition().y, center });
				dir = nextDir;
			}
		}
	}
	*/

	//turnHero();
}

void Hero::turnHero() {
	if (nextDir != dir) {
		Vector3 rotPos = getPosition() / cte::SCALE_CUBE;
		rotPos = { floor(rotPos.x), floor(rotPos.y), floor(rotPos.z) };

		Vector3 orientation = getOrientation();

		if (nextDir.x == -1 && !lab->isWall(rotPos + nextDir)) { // LEFT
			Radian r = Radian(180.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
		if (nextDir.x == 1 && !lab->isWall(rotPos + nextDir)) { // RIGHT
			Radian r = Radian(0.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
		if (nextDir.z == -1 && !lab->isWall(rotPos + nextDir)) { // UP
			Radian r = Radian(90.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
		if (nextDir.z == 1 && !lab->isWall(rotPos + nextDir)) { // UP
			Radian r = Radian(270.f - orientation.y);
			yaw(r);
			dir = nextDir;
		}
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
		default:
			break;
	}
	return true;
}