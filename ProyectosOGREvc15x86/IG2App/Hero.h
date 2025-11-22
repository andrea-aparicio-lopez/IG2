#pragma once

#include "Character.h"

class Labyrinth;

#include <OgreTrays.h>

class GameScene;
class Hero : public Character {
public:
	Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, GameScene* scene);
	~Hero();


protected:
	int _health = 3;
	int _score = 0;
	bool _isImmune = false;
	double _immunityTime;

	GameScene* _gameScene;
public:
	inline int health() const { return _health; }
	inline int score() const { return _score; }

	void moveCharacter(double dt) override;

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	void damageHero();

	void placeBomb();

protected:
	void resetHeroPos();
};