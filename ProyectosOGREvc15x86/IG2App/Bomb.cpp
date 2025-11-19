#include "Bomb.h"
#include "Constants.h"

Bomb::Bomb(Vector3 position, SceneNode* node, SceneManager* sM): IG2Object(position, node, sM, "sphere.mesh") 
{
	entity->getParentSceneNode()->_update(true, true);
	auto s = getAABB().getSize();
	s = cte::BOMB_MAX_SIZE / s;
	setScale(s);

	setMaterialName("Bomb");


	_fuse = new IG2Object(Vector3(0, getAABB().getSize().y/2, 0), mNode->createChildSceneNode(), mSM, "column.mesh");
	_fuse->setScale(Vector3(0.15));
	_fuse->setMaterialName("BombFuse");

}

Bomb::~Bomb() {
	delete _fuse;

	IG2Object::~IG2Object();
}

