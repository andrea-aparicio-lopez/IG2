#pragma once

#include "Character.h"

class Labyrinth;

#include <OgreTrays.h>

class Hero : public Character {
public:
	Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, OgreBites::TextBox* heroAttributesDisplay);
	~Hero();


protected:
	int _health = 3;
	int _score = 0;

	OgreBites::TextBox* _heroAttributesDisplay;

public:
	inline int health() const { return _health; }
	inline int score() const { return _score; }

	void moveCharacter(double dt) override;

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	void damageHero();

};