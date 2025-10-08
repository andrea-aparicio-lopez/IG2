#pragma once

#include "IG2Object.h"

class Labyrinth;
class Hero : public IG2Object {
public:
	Hero(Vector3 position, SceneNode* node, SceneManager* sM);
	~Hero();


protected:
	int health = 3;
	int score = 0;

	Vector2 dir;
	Vector2 nextDir;

	Labyrinth* lab;

public:
	inline int health() const {return health;}
	inline int score() const {return score;}

	void setNewDir(Vector2 const& nDir);

	void moveHero(); 

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

};