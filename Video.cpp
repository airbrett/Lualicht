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

	video.set("EMF_WIREFRAME", irr::video::EMF_WIREFRAME);
	video.set("EMF_POINTCLOUD", irr::video::EMF_POINTCLOUD);
	video.set("EMF_GOURAUD_SHADING", irr::video::EMF_GOURAUD_SHADING);
	video.set("EMF_LIGHTING", irr::video::EMF_LIGHTING);
	video.set("EMF_ZBUFFER", irr::video::EMF_ZBUFFER);
	video.set("EMF_ZWRITE_ENABLE", irr::video::EMF_ZWRITE_ENABLE);
	video.set("EMF_BACK_FACE_CULLING", irr::video::EMF_BACK_FACE_CULLING);
	video.set("EMF_FRONT_FACE_CULLING", irr::video::EMF_FRONT_FACE_CULLING);
	video.set("EMF_BILINEAR_FILTER", irr::video::EMF_BILINEAR_FILTER);
	video.set("EMF_TRILINEAR_FILTER", irr::video::EMF_TRILINEAR_FILTER);
	video.set("EMF_ANISOTROPIC_FILTER", irr::video::EMF_ANISOTROPIC_FILTER);
	video.set("EMF_FOG_ENABLE", irr::video::EMF_FOG_ENABLE);
	video.set("EMF_NORMALIZE_NORMALS", irr::video::EMF_NORMALIZE_NORMALS);
	video.set("EMF_TEXTURE_WRAP", irr::video::EMF_TEXTURE_WRAP);
	video.set("EMF_ANTI_ALIASING", irr::video::EMF_ANTI_ALIASING);
	video.set("EMF_COLOR_MASK", irr::video::EMF_COLOR_MASK);
	video.set("EMF_COLOR_MATERIAL", irr::video::EMF_COLOR_MATERIAL);
	video.set("EMF_USE_MIP_MAPS", irr::video::EMF_USE_MIP_MAPS);
	video.set("EMF_BLEND_OPERATION", irr::video::EMF_BLEND_OPERATION);
	video.set("EMF_POLYGON_OFFSET", irr::video::EMF_POLYGON_OFFSET);
	video.set("EMF_BLEND_FACTOR", irr::video::EMF_BLEND_FACTOR);

	video.set("EMT_SOLID", irr::video::EMT_SOLID);
	video.set("EMT_SOLID_2_LAYER", irr::video::EMT_SOLID_2_LAYER);
	video.set("EMT_LIGHTMAP", irr::video::EMT_LIGHTMAP);
	video.set("EMT_LIGHTMAP_ADD", irr::video::EMT_LIGHTMAP_ADD);
	video.set("EMT_LIGHTMAP_M2", irr::video::EMT_LIGHTMAP_M2);
	video.set("EMT_LIGHTMAP_M4", irr::video::EMT_LIGHTMAP_M4);
	video.set("EMT_LIGHTMAP_LIGHTING", irr::video::EMT_LIGHTMAP_LIGHTING);
	video.set("EMT_LIGHTMAP_LIGHTING_M2", irr::video::EMT_LIGHTMAP_LIGHTING_M2);
	video.set("EMT_LIGHTMAP_LIGHTING_M4", irr::video::EMT_LIGHTMAP_LIGHTING_M4);
	video.set("EMT_DETAIL_MAP", irr::video::EMT_DETAIL_MAP);
	video.set("EMT_SPHERE_MAP", irr::video::EMT_SPHERE_MAP);
	video.set("EMT_REFLECTION_2_LAYER", irr::video::EMT_REFLECTION_2_LAYER);
	video.set("EMT_TRANSPARENT_ADD_COLOR", irr::video::EMT_TRANSPARENT_ADD_COLOR);
	video.set("EMT_TRANSPARENT_ALPHA_CHANNEL", irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	video.set("EMT_TRANSPARENT_ALPHA_CHANNEL_REF", irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	video.set("EMT_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
	video.set("EMT_TRANSPARENT_REFLECTION_2_LAYER", irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER);
	video.set("EMT_NORMAL_MAP_SOLID", irr::video::EMT_NORMAL_MAP_SOLID);
	video.set("EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR", irr::video::EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR);
	video.set("EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA);
	video.set("EMT_PARALLAX_MAP_SOLID", irr::video::EMT_PARALLAX_MAP_SOLID);
	video.set("EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR", irr::video::EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR);
	video.set("EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA);
	video.set("EMT_ONETEXTURE_BLEND", irr::video::EMT_ONETEXTURE_BLEND);

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
		"color", &irr::video::SColor::color,
		"getRed", &irr::video::SColor::getRed,
		"getGreen", &irr::video::SColor::getGreen,
		"getBlue", &irr::video::SColor::getBlue
	);

	return video;
}