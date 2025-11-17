#include "Bomb.h"

Bomb::Bomb(Vector3 position, SceneNode* node, SceneManager* sM): IG2Object(position, node, sM, "sphere.mesh") {
	setScale(Vector3(0.5f));
}