#pragma once

#include <irrlicht.h>
#include "sol/sol.hpp"

class SceneNodeAnimator : public irr::scene::ISceneNodeAnimator
{
private:
	sol::table mEntity;

public:
	SceneNodeAnimator(sol::table Entity);
	void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
	irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
};