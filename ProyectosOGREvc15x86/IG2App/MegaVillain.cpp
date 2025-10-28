#include "MegaVillain.h"
#include <cmath>
#include <OgreMath.h>

MegaVillain::MegaVillain(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab): Villain(position, node, sM, lab, "athene.mesh"), fishTimer(), knotTimer(){
	fishTimer.reset();
	knotTimer.reset();
	torque = node->createChildSceneNode();
	torque->setPosition(0, 100, 0);

	for (int i = 0; i < NUM_PECES; i++) {
		float currentDegree = 360 / NUM_PECES;
		currentDegree *= i;

		auto fish = new IG2Object(Vector3(cos(currentDegree * M_PI/180.0) * FISH_DISTANCE, 0, sin(currentDegree * M_PI / 180.0) * FISH_DISTANCE), torque->createChildSceneNode(), sM, "fish.mesh");
		parts.push_back(fish);
		fish->setScale(Vector3(4));
		fish->yaw(Radian(Real(45)));

		auto knotTorque = fish->createChildSceneNode();
		knotTorque->setPosition(Vector3(0,0,0));
		for (int j = 0; j < NUM_KNOTS; j++) {
			float currentKnotDegree = 360 / NUM_KNOTS;
			currentKnotDegree *= j;
			auto knot = new IG2Object(Vector3(cos(currentKnotDegree * M_PI / 180.0) * KNOT_DISTANCE, sin(currentKnotDegree * M_PI / 180.0) * KNOT_DISTANCE, 0),knotTorque->createChildSceneNode(), sM, "knot.mesh");
			parts.push_back(knot);
			knot->setScale(Vector3(0.01));

		}
		knotTorques.push_back(knotTorque);
	}
}

MegaVillain::~MegaVillain() {
	for (auto p : parts) delete p;
	Villain::~Villain();
}

void MegaVillain::moveCharacter(double dt) {
	Villain::moveCharacter(dt);
	
	torque->yaw(Radian(FISH_ROTATION_VELOCITY*M_PI/180.0) * fishDirection);

	for (auto knot : knotTorques) {
		knot->roll(Radian(KNOT_ROTATION_VELOCITY*M_PI / 180) *knotDirection);
	}

	if (fishTimer.getMilliseconds() >= FISH_TIMER_DURATION) {
		fishTimer.reset();
		fishDirection = -fishDirection;
	}

	if (knotTimer.getMilliseconds() >= KNOT_TIMER_DURATION) {
		knotTimer.reset();
		knotDirection = -knotDirection;
	}

}