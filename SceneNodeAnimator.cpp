#include "SceneNodeAnimator.h"

#include <limits>

SceneNodeAnimator::SceneNodeAnimator(sol::table Entity) :
	mEntity(Entity)
{
}

void SceneNodeAnimator::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
{
	sol::function Func = mEntity["Update"];
	if (Func)
		Func(mEntity);
}

irr::scene::ISceneNodeAnimator* SceneNodeAnimator::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
{
	//what to do with node and newManager?
	return new SceneNodeAnimator(mEntity);
}
