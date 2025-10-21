#include "Villain.h"
#include "Constants.h"
#include "Labyrinth.h"
#include <cmath>
#include <random>
#include <iostream>

Villain::Villain(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab)
	: Character(position, node, sM, lab, "ogrehead.mesh")
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = cte::SCALE_VILLAIN / s;
	setScale(s);

	lastDirChange = { 0,0,0 };

}

Villain::~Villain() {
	Character::~Character();
}

void Villain::moveCharacter(double dt) {
	// mover al villano en función de su velocidad
	// comprobar si está en intersección o contra una pared, en cuyo caso selecciona 
	// la siguiente dirección de forma aleatoria entre las posibles
	// Dejar que la lógica de moveCharacter haga su magia
	move(dir * cte::VILLAIN_VEL * dt);

	changeDir();

	Character::moveCharacter(dt);
}

void Villain::changeDir() {
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

	if (taspasao && lastDirChange != flooredPos) {
		std::vector<Vector3> possibleDirs;
		// Posibles direcciones, excepto 180º
		for (auto d : directions) {
			if(d != dir *(-1) && !lab->isWall(flooredPos + d))
				possibleDirs.push_back(d);
		}
		
		if (possibleDirs.size() > 0) {
			int i = std::rand() % possibleDirs.size();
			setNewDir(possibleDirs[i]);
		}
		else setNewDir(dir * (-1));

		lastDirChange = flooredPos;
	}
}