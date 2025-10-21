#include "Character.h"
#include "Constants.h"
#include "Labyrinth.h"
#include <cmath>
#include <iostream>

Character::Character(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, std::string mesh)
	: IG2Object(position, node, sM, mesh)
	, lab(lab)
{

}

Character::~Character() {

}


void Character::setNewDir(Vector3 const& nDir) {
	nextDir = nDir;
}

void Character::frameRendered(const Ogre::FrameEvent& evt) {
	moveCharacter(evt.timeSinceLastFrame);
}


void Character::moveCharacter(double dt) {
	// comprobar si hay colision
	// si hay: devolver al personaje a la posición más cercana válida
	// comprobar si puede girar
	// si puede: rotar al personaje y cambiar direccion

	Vector3 pos = getPosition() + Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5;
	pos /= cte::SCALE_CUBE;
	Vector3 flooredPos = { floor(pos.x), floor(pos.y), floor(pos.z) };

	Vector3 center = flooredPos + Vector3(0.5, 0, 0.5);

	bool taspasao = false;

	if (dir.z > 0 && pos.z > center.z) {
		taspasao = true;
	}
	if (dir.z < 0 && pos.z < center.z) {
		taspasao = true;
	}
	if (dir.x > 0 && pos.x > center.x) {
		taspasao = true;
	}
	if (dir.x < 0 && pos.x < center.x) {
		taspasao = true;
	}

	if (taspasao) {
		if (!lab->isWall(flooredPos + nextDir) && dir != nextDir) {
			setPosition(center * cte::SCALE_CUBE - Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5);
			dir = nextDir;
			turnCharacter();
		}

		if (lab->isWall(flooredPos + dir)) {
			setPosition(center * cte::SCALE_CUBE - Vector3(cte::SCALE_CUBE, 0, cte::SCALE_CUBE) * 0.5);
		}
	}
}

void Character::turnCharacter() {
	Quaternion q = this->getOrientation().getRotationTo(dir);
	mNode->rotate(q);
}