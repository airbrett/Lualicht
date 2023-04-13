#include <irrlicht.h>

#include <lua.hpp>
#include "sol/sol.hpp"

#include "Core.h"
#include "Video.h"
#include "lua_IrrAssimp.h"
#include "EventReceiver.h"
#include "Scene.h"
#include "GUI.h"
#include "SceneNodeAnimator.h"
#include "Helpers.h"

extern "C" __declspec(dllexport) int luaopen_Lualicht(lua_State* L);



sol::table Lualicht(sol::this_state L)
{
	sol::state_view lua(L);
	sol::table irrlict = lua.create_table();

	irrlict.new_usertype<irr::IrrlichtDevice>(
		"IrrlichtDevice", sol::no_constructor,
		"getVideoDriver", &irr::IrrlichtDevice::getVideoDriver,
		"getSceneManager", &irr::IrrlichtDevice::getSceneManager,
		"getCursorControl", &irr::IrrlichtDevice::getCursorControl,
		"getGUIEnvironment", &irr::IrrlichtDevice::getGUIEnvironment,
		"getTimer", &irr::IrrlichtDevice::getTimer,
		"run", &irr::IrrlichtDevice::run,
		"isWindowActive", &irr::IrrlichtDevice::isWindowActive,
		"setWindowCaption", [](irr::IrrlichtDevice& device, const char* text) {
			const wchar_t* wtext = char_to_wchar(text);
			device.setWindowCaption(wtext);
			delete [] wtext;
		},
		"yield", &irr::IrrlichtDevice::yield
	);

	irrlict.set("createDevice", sol::overload(
		[]()
			{return irr::createDevice(); },
		[](irr::video::E_DRIVER_TYPE driverType)
			{return irr::createDevice(driverType); },
		[](irr::video::E_DRIVER_TYPE driverType, sol::table windowSize)
		{return irr::createDevice(driverType, { windowSize["Width"], windowSize["Height"] }); },
		[](irr::video::E_DRIVER_TYPE driverType, sol::table windowSize, irr::u32 bits)
			{return irr::createDevice(driverType, { windowSize["Width"], windowSize["Height"] }, bits); },
		[](irr::video::E_DRIVER_TYPE driverType, sol::table windowSize, irr::u32 bits, bool fullscreen)
			{return irr::createDevice(driverType, { windowSize["Width"], windowSize["Height"] }, bits, fullscreen); },
		[](irr::video::E_DRIVER_TYPE driverType, sol::table windowSize, irr::u32 bits, bool fullscreen, bool stencilbuffer)
			{return irr::createDevice(driverType, { windowSize["Width"], windowSize["Height"] }, bits, fullscreen, stencilbuffer); },
		[](irr::video::E_DRIVER_TYPE driverType, sol::table windowSize, irr::u32 bits, bool fullscreen, bool stencilbuffer, bool vsync)
			{return irr::createDevice(driverType, { windowSize["Width"], windowSize["Height"] }, bits, fullscreen, stencilbuffer, vsync); },
		[](irr::video::E_DRIVER_TYPE driverType, sol::table windowSize, irr::u32 bits, bool fullscreen, bool stencilbuffer, bool vsync, sol::table& Receiver)
			{
				EventReceiver* Rcvr = new EventReceiver(Receiver);
				return irr::createDevice(driverType, { windowSize["Width"], windowSize["Height"] }, bits, fullscreen, stencilbuffer, vsync, Rcvr);
			}
		)
	);

	irrlict.new_usertype<irr::ITimer>(
		"ITimer", sol::no_constructor,
		"getRealTime", &irr::ITimer::getRealTime
	);

	irrlict.set("EET_GUI_EVENT", irr::EET_GUI_EVENT);
	irrlict.set("EET_MOUSE_INPUT_EVENT", irr::EET_MOUSE_INPUT_EVENT);
	irrlict.set("EET_KEY_INPUT_EVENT", irr::EET_KEY_INPUT_EVENT);
	irrlict.set("EET_TOUCH_INPUT_EVENT", irr::EET_TOUCH_INPUT_EVENT);
	irrlict.set("EET_JOYSTICK_INPUT_EVENT", irr::EET_JOYSTICK_INPUT_EVENT);
	irrlict.set("EET_LOG_TEXT_EVENT", irr::EET_LOG_TEXT_EVENT);
	irrlict.set("EET_USER_EVENT", irr::EET_USER_EVENT);

	irrlict.new_usertype<irr::SEvent::SKeyInput>(
		"SKeyInput", sol::no_constructor,
		"Key", &irr::SEvent::SKeyInput::Key,
		"PressedDown", [](irr::SEvent::SKeyInput& SKeyInput) { return SKeyInput.PressedDown; }
	);

	irrlict.new_usertype<irr::SEvent::SMouseInput>(
		"SMouseInput", sol::no_constructor,
		"X", &irr::SEvent::SMouseInput::X,
		"Y", &irr::SEvent::SMouseInput::Y,
		"isLeftPressed", &irr::SEvent::SMouseInput::isLeftPressed,
		"isRightPressed", &irr::SEvent::SMouseInput::isRightPressed
	);

	irrlict.new_usertype<irr::SEvent>(
		"SEvent", sol::no_constructor,
		"EventType", &irr::SEvent::EventType,
		"MouseInput", &irr::SEvent::MouseInput,
		"KeyInput", &irr::SEvent::KeyInput
	);
	
	irrlict.set("video", InitVideo(L));
	irrlict.set("scene", InitScene(L));
	irrlict.set("gui", InitGUI(L));

	sol::table io = lua.create_table();

	io.new_usertype<irr::io::path>(
		"path",
		sol::constructors<irr::io::path(), irr::io::path(const irr::fschar_t* const)>()
	);

	irrlict.set("io", io);

	irrlict.set("core", InitCore(L));
	irrlict.set("irrassimp", InitIrrAssimp(L));


	sol::table custom = lua.create_table();

	custom.new_usertype<SceneNodeAnimator>(
		"SceneNodeAnimator", sol::constructors <SceneNodeAnimator(sol::table)>(),
		sol::base_classes, sol::bases<irr::scene::ISceneNodeAnimator>()
	);

	irrlict.set("custom", custom);

	return irrlict;
}

int luaopen_Lualicht(lua_State* L)
{
	return sol::stack::call_lua(L, 1, Lualicht);
}