#include "Core.h"
#include <irrlicht.h>

sol::table InitCore(sol::this_state L)
{
	sol::state_view lua(L);
	sol::table core = lua.create_table();

	
	core.new_usertype<irr::core::dimension2du>(
		"dimension2du",
		sol::constructors<irr::core::dimension2du(), irr::core::dimension2du(irr::u32, irr::u32)>(),
		"Width", &irr::core::dimension2du::Width,
		"Height", &irr::core::dimension2du::Height
	);

	core.new_usertype<irr::core::vector2df>(
		"vector2df",
		sol::constructors<irr::core::vector2df(), irr::core::vector2df(irr::core::vector2df), irr::core::vector2df(irr::f32, irr::f32)>(),
		"x", &irr::core::vector2df::X,
		"y", &irr::core::vector2df::Y,
		sol::meta_function::addition, sol::resolve<irr::core::vector2df(const irr::core::vector2df&) const>(&irr::core::vector2df::operator+),
		sol::meta_function::subtraction, sol::resolve<irr::core::vector2df(const irr::core::vector2df&) const>(&irr::core::vector2df::operator-),
		sol::meta_function::equal_to, sol::resolve<bool(const irr::core::vector2df&) const>(&irr::core::vector2df::operator==)
	);

	core.new_usertype<irr::core::vector2di>(
		"vector2di",
		sol::constructors<irr::core::vector2di(), irr::core::vector2di(irr::core::vector2di), irr::core::vector2di(irr::s32, irr::s32)>(),
		"x", &irr::core::vector2di::X,
		"y", &irr::core::vector2di::Y,
		sol::meta_function::addition, sol::resolve<irr::core::vector2di(const irr::core::vector2di&) const>(&irr::core::vector2di::operator+),
		sol::meta_function::subtraction, sol::resolve<irr::core::vector2di(const irr::core::vector2di&) const>(&irr::core::vector2di::operator-),
		sol::meta_function::equal_to, sol::resolve<bool(const irr::core::vector2di&) const>(&irr::core::vector2di::operator==)
		);

	core.new_usertype<irr::core::vector3df>(
		"vector3df",
		sol::constructors<irr::core::vector3df(), irr::core::vector3df(irr::core::vector3df), irr::core::vector3df(irr::f32, irr::f32, irr::f32)>(),
		"x", &irr::core::vector3df::X,
		"y", &irr::core::vector3df::Y,
		"z", &irr::core::vector3df::Z,
		sol::meta_function::addition, sol::resolve<irr::core::vector3df(const irr::core::vector3df&) const>(&irr::core::vector3df::operator+),
		sol::meta_function::subtraction, sol::resolve<irr::core::vector3df(const irr::core::vector3df&) const>(&irr::core::vector3df::operator-),
		sol::meta_function::equal_to, sol::resolve<bool(const irr::core::vector3df&) const>(&irr::core::vector3df::operator==)
	);

	core.new_usertype<irr::core::recti>(
		"recti",
		sol::constructors<irr::core::recti(), irr::core::recti(irr::u32, irr::u32, irr::u32, irr::u32)>()
	);

	sol::table eConstructor = lua.create_table();

	eConstructor.set("EM4CONST_NOTHING", irr::core::matrix4::EM4CONST_NOTHING);
	eConstructor.set("EM4CONST_COPY", irr::core::matrix4::EM4CONST_COPY);
	eConstructor.set("EM4CONST_IDENTITY", irr::core::matrix4::EM4CONST_IDENTITY);
	eConstructor.set("EM4CONST_TRANSPOSED", irr::core::matrix4::EM4CONST_TRANSPOSED);
	eConstructor.set("EM4CONST_INVERSE", irr::core::matrix4::EM4CONST_INVERSE);
	eConstructor.set("EM4CONST_INVERSE_TRANSPOSED", irr::core::matrix4::EM4CONST_INVERSE_TRANSPOSED);

	core.new_usertype<irr::core::matrix4>(
		"matrix4",
		sol::constructors<irr::core::matrix4(), irr::core::matrix4(irr::core::matrix4::eConstructor)>(),
		"transformVect", sol::resolve<void(irr::core::vector3df&) const>(&irr::core::matrix4::transformVect),
		"setTranslation", &irr::core::matrix4::setTranslation,
		"setRotationDegrees", &irr::core::matrix4::setRotationDegrees,
		"setScale", [](irr::core::matrix4& mat, sol::table scale) { mat.setScale({ scale["x"], scale["y"], scale["z"] }); },
		"eConstructor", eConstructor
	);

	core.new_usertype<irr::core::plane3df>(
		"plane3df",
		sol::constructors<irr::core::plane3df(), irr::core::plane3df(irr::core::vector3df, irr::core::vector3df)>(),
		"getIntersectionWithLimitedLine", &irr::core::plane3df::getIntersectionWithLimitedLine
	);

	core.new_usertype<irr::core::line3df>(
		"line3df",
		sol::constructors<irr::core::line3df(), irr::core::line3df(irr::f32 xa, irr::f32 ya, irr::f32 za, irr::f32 xb, irr::f32 yb, irr::f32 zb)>()
	);

	core.new_usertype<irr::core::triangle3df>(
		"triangle3df",
		sol::constructors<irr::core::triangle3df(), irr::core::triangle3df(const irr::core::vector3df& v1, const irr::core::vector3df& v2, const irr::core::vector3df& v3)>()
	);

	return core;
}