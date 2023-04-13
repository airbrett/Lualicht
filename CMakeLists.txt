cmake_minimum_required(VERSION 3.17)

project(Lualicht)

find_package(Lua REQUIRED)
find_package(Irrlicht REQUIRED)
find_package(Assimp REQUIRED)
find_package(IrrAssimp REQUIRED)

add_library(Lualicht SHARED
	Core.h
	Core.cpp
	EventReceiver.h
	EventReceiver.cpp
	GUI.h
	GUI.cpp
	Helpers.h
	Helpers.cpp
	Irr.cpp
	lua_IrrAssimp.h
	lua_IrrAssimp.cpp
	Scene.h
	Scene.cpp
	SceneNodeAnimator.h
	SceneNodeAnimator.cpp
	Video.h
	Video.cpp
)

target_include_directories(Lualicht
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE ${LUA_INCLUDE_DIR}
)

target_compile_features(Lualicht PRIVATE cxx_std_17)

target_link_libraries(Lualicht
	${LUA_LIBRARIES}
	Irrlicht
	assimp::assimp
	IrrAssimp
)