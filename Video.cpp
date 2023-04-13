#include "Video.h"

#include <irrlicht.h>

#include "Helpers.h"

sol::table InitVideo(sol::this_state L)
{
	sol::state_view lua(L);

	sol::table video = lua.create_table();
	video.set("EDT_NULL", irr::video::EDT_NULL);
	video.set("EDT_SOFTWARE", irr::video::EDT_SOFTWARE);
	video.set("EDT_BURNINGSVIDEO", irr::video::EDT_BURNINGSVIDEO);
	video.set("EDT_DIRECT3D9", irr::video::EDT_DIRECT3D9);
	video.set("EDT_OPENGL", irr::video::EDT_OPENGL);

	video.set("ECBF_NONE", irr::video::ECBF_NONE);
	video.set("ECBF_COLOR", irr::video::ECBF_COLOR);
	video.set("ECBF_DEPTH", irr::video::ECBF_DEPTH);
	video.set("ECBF_STENCIL", irr::video::ECBF_STENCIL);
	video.set("ECBF_ALL", irr::video::ECBF_ALL);

	video.new_usertype<irr::video::IVideoDriver>(
		"IVideoDriver", sol::no_constructor,
		"beginScene", sol::overload(
			[](irr::video::IVideoDriver& driver) {return driver.beginScene(); },
			[](irr::video::IVideoDriver& driver, irr::u16 clearFlag) {return driver.beginScene(clearFlag); }
		),
		"endScene", &irr::video::IVideoDriver::endScene,
		"getFPS", &irr::video::IVideoDriver::getFPS,
		"getName", &irr::video::IVideoDriver::getName,
		"draw2DRectangle", sol::overload(
			[](irr::video::IVideoDriver& driver, irr::video::SColor color, const irr::core::recti& pos) { driver.draw2DRectangle(color, pos); },
			[](irr::video::IVideoDriver& driver, const sol::table& color, const sol::table& pos)
			{
				driver.draw2DRectangle(
					{color[1], color[2], color[3], color[4]},
					{ToS32(pos[1]), ToS32(pos[2]), ToS32(pos[3]), ToS32(pos[4])}
				);
			}
		),
		"draw2DImage",
			[](irr::video::IVideoDriver& driver, irr::video::ITexture* texture, const sol::table& destRect, const sol::table& sourceRect)
			{
				driver.draw2DImage(texture,
					irr::core::recti(ToS32(destRect["x1"]), ToS32(destRect["y1"]), ToS32(destRect["x2"]), ToS32(destRect["y2"])),
					irr::core::recti(ToS32(sourceRect["x1"]), ToS32(sourceRect["y1"]), ToS32(sourceRect["x2"]), ToS32(sourceRect["y2"])),
					0,0,true
				);
			},
		"getScreenSize", &irr::video::IVideoDriver::getScreenSize,
		"getTexture", [](irr::video::IVideoDriver& driver, const char* filename) { return driver.getTexture(filename); }
	);

	video.new_usertype<irr::video::S3DVertex>(
		"S3DVertex", sol::no_constructor,
		"Pos", &irr::video::S3DVertex::Pos,
		"Normal", &irr::video::S3DVertex::Normal,
		"Color", &irr::video::S3DVertex::Color,
		"TCoords", &irr::video::S3DVertex::TCoords
	);

	video.new_usertype<irr::video::SColorf>(
		"SColorf", sol::constructors<irr::video::SColorf(), irr::video::SColorf(irr::f32, irr::f32, irr::f32, irr::f32), irr::video::SColorf(irr::video::SColorf)>(),
		"r", &irr::video::SColorf::r,
		"g", &irr::video::SColorf::g,
		"b", &irr::video::SColorf::b,
		"a", &irr::video::SColorf::a
	);

	video.new_usertype<irr::video::SColor>(
		"SColor", sol::constructors<irr::video::SColor(), irr::video::SColor(irr::s32, irr::s32, irr::s32, irr::s32), irr::video::SColor(irr::video::SColor)>(),
		"color", &irr::video::SColor::color
	);

	return video;
}