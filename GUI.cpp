#include "GUI.h"
#include <irrlicht.h>

#include "Helpers.h"

sol::table InitGUI(sol::this_state L)
{
	sol::state_view lua(L);
	sol::table gui = lua.create_table();

	gui.new_usertype<irr::gui::ICursorControl>(
		"ICursorControl", sol::no_constructor,
		"setPosition", sol::overload(
			sol::resolve<void(irr::f32, irr::f32)>(&irr::gui::ICursorControl::setPosition),
			sol::resolve<void(const irr::core::vector2df&)>(&irr::gui::ICursorControl::setPosition)
		),
		"getRelativePosition", sol::overload(
			&irr::gui::ICursorControl::getRelativePosition,
			[](irr::gui::ICursorControl& cc) { return cc.getRelativePosition(); }
		),
		"setVisible", &irr::gui::ICursorControl::setVisible
	);

	gui.new_usertype<irr::gui::IGUIEnvironment>(
		"IGUIEnvironment", sol::no_constructor,
		"getBuiltInFont", &irr::gui::IGUIEnvironment::getBuiltInFont,
		"getFont", [](irr::gui::IGUIEnvironment& genv, const char* text) { return genv.getFont(text); }
	);

	gui.new_usertype<irr::gui::IGUIFont>(
		"IGUIFont", sol::no_constructor,
		"draw", sol::overload(
			[](irr::gui::IGUIFont& font, const char* text, const sol::table& pos, const sol::table& color) {
				const wchar_t* wtext = char_to_wchar(text);
				font.draw(wtext,
					irr::core::recti(ToS32(pos["x1"]), ToS32(pos["y1"]), ToS32(pos["x2"]), ToS32(pos["y2"])),
					irr::video::SColor(ToS32(color["a"]), ToS32(color["r"]), ToS32(color["g"]), ToS32(color["b"])));

				delete[] wtext;
				return;
			},
			[](irr::gui::IGUIFont& font, const char* text, const sol::table& pos, const sol::table& color, bool hcenter) {
				const wchar_t* wtext = char_to_wchar(text);
				font.draw(wtext,
					irr::core::recti(ToS32(pos["x1"]), ToS32(pos["y1"]), ToS32(pos["x2"]), ToS32(pos["y2"])),
					irr::video::SColor(ToS32(color["a"]), ToS32(color["r"]), ToS32(color["g"]), ToS32(color["b"])),
					hcenter);

				delete[] wtext;
				return;
			},
			[](irr::gui::IGUIFont& font, const char* text, const sol::table& pos, const sol::table& color, bool hcenter, bool vcenter) {
				const wchar_t* wtext = char_to_wchar(text);
				font.draw(wtext,
					irr::core::recti(ToS32(pos["x1"]), ToS32(pos["y1"]), ToS32(pos["x2"]), ToS32(pos["y2"])),
					irr::video::SColor(ToS32(color["a"]), ToS32(color["r"]), ToS32(color["g"]), ToS32(color["b"])),
					hcenter,
					vcenter);

				delete[] wtext;
				return;
			})
	);

	return gui;
}
