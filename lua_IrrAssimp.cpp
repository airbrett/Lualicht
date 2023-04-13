#include "lua_IrrAssimp.h"

#include <irrlicht.h>
#include <IrrAssimp.h>


sol::table InitIrrAssimp(sol::this_state L)
{
	sol::state_view lua(L);

	sol::table irrassimp = lua.create_table();

	irrassimp.new_usertype<IrrAssimpImport>(
		"IrrAssimpImport", sol::constructors<IrrAssimpImport(irr::scene::ISceneManager*)>(),
		sol::base_classes, sol::bases<irr::scene::IMeshLoader>()
	);

	return irrassimp;
}
