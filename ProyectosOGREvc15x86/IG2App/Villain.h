#pragma once

#include "Character.h"
class Labyrinth;

class Villain : public Character {
public:
	Villain(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab);
	~Villain();

	void moveCharacter(double dt) override;

protected:
	Vector3 lastDirChange;
	void changeDir();
};

