#include "Wall.h"
#include "Constants.h"

Wall::Wall(Vector3 pos, SceneNode* mazeNode, SceneManager* sM):IG2Object(pos, mazeNode->createChildSceneNode(), sM, "cube.mesh")
{
	entity->getParentSceneNode()->_update(true, true);
	//auto s = calculateBoxSize();	
	auto s = getAABB().getSize();
	s = cte::SCALE_CUBE / s ;
	setScale(s);
}

Wall::~Wall() {
	IG2Object::~IG2Object();
}