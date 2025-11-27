#pragma once

#include "Character.h"
class Labyrinth;

class Villain : public Character {
public:
	Villain(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, std::string mesh = "ogrehead.mesh");
	~Villain();

	virtual void moveCharacter(double dt) override;

	void damageVillain();
	bool isDead() const;

protected:
	void changeDir();

	Vector3 lastDirChange;
	bool _dead = false;
};

