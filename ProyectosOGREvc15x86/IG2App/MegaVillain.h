#pragma once
#include "Villain.h"
class MegaVillain: public Villain
{
public:
	MegaVillain(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab);
	~MegaVillain();
	
	void moveCharacter(double dt) override;

private:
	const int NUM_PECES = 5;
	const int NUM_KNOTS = 15;
	const float FISH_DISTANCE = 30;
	const float KNOT_DISTANCE = 3;

	SceneNode* torque;
	std::vector<SceneNode*> knotTorques;
};

