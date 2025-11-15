#pragma once
#include "IG2Object.h"
class AnimCharacter : public IG2Object
{
public:
	AnimCharacter(Vector3 iitPos, SceneNode* node, SceneManager* sM, std::string mesh);
	~AnimCharacter();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	AnimationState* getAnimationState(std::string anim);
};

