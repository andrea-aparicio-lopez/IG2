#include "Hero.h"
#include "Constants.h"

Hero::Hero(Vector3 position, SceneNode* node, SceneManager* sM) 
: IG2Object(position, node->createChildSceneNode(), sM, "Sinbad.mesh")
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = cte::SCALE_HERO / s ;
	setScale(s);
}