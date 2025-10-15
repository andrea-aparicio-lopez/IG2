#pragma once

#include "IG2Object.h"

class Labyrinth;

class Hero : public IG2Object {
public:
	Hero(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab);
	~Hero();


protected:
	int _health = 3;
	int _score = 0;

	Vector3 dir = {0,0,1};
	Vector3 nextDir = {0,0,1};

	Labyrinth* lab;

public:
	inline int health() const { return _health; }
	inline int score() const { return _score; }

	void setNewDir(Vector3 const& nDir);

	void moveHero(double dt); 
	void turnHero();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

};