#include "AnimCharacter.h"

AnimCharacter::AnimCharacter(Vector3 initPos, SceneNode* node, SceneManager* sM, std::string mesh)
	: IG2Object(initPos, node, sM, mesh)
{

}

AnimCharacter::~AnimCharacter() {
	IG2Object::~IG2Object();
}

void AnimCharacter::frameRendered(const Ogre::FrameEvent& evt) {
	auto anims = entity->getAllAnimationStates()->getEnabledAnimationStates();
	for (auto a : anims)
		a->addTime(evt.timeSinceLastEvent);
}

AnimationState* AnimCharacter::getAnimationState(std::string anim) {
	return entity->getAnimationState(anim);
}