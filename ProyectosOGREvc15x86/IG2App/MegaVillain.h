#pragma once
#include "Villain.h"
#include <OgreTimer.h>
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
	const float FISH_TIMER_DURATION = 1000;
	const float KNOT_TIMER_DURATION = 500;

	const float FISH_ROTATION_VELOCITY = 1;
	const float KNOT_ROTATION_VELOCITY = 5;

	SceneNode* torque;
	std::vector<SceneNode*> knotTorques;

	std::vector<IG2Object*> parts;
	Ogre::Timer fishTimer;
	Ogre::Timer knotTimer;
	int fishDirection = 1;
	int knotDirection = 1;
};

