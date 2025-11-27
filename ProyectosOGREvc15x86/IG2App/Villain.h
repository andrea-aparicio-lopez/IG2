#pragma once

#include "Character.h"
class Labyrinth;

class Villain : public Character {
public:
	Villain(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, std::string mesh = "ogrehead.mesh");
	~Villain();

	virtual void moveCharacter(double dt) override;

	void damageVillain();

protected:
	Vector3 lastDirChange;
	void changeDir();
};

