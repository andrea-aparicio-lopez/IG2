#pragma once

#include "IG2Object.h"

class Hero : public IG2Object {
public:
	Hero(Vector3 position, SceneNode* node, SceneManager* sM);
};