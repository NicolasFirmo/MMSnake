#include "mouse_event.h"

std::string MouseButtonEvent::toString() const {
	return fmt::format("MouseButtonEvent{{button:{}, action:{}, mods:{}{}{}}}",
					   button == MouseButton::left	 ? "left" :
					   button == MouseButton::right	 ? "right" :
					   button == MouseButton::middle ? "middle" :
													   "unknown",
					   action == MouseAction::pressed ? "pressed" : "released",
					   mods & MouseMods::shift && mods & ~MouseMods::shift ? "shift+" :
					   mods & MouseMods::shift							   ? "shift" :
																			 "",
					   mods & MouseMods::ctrl && mods & ~MouseMods::ctrl ? "ctrl+" :
					   mods & MouseMods::ctrl							 ? "ctrl" :
																		   "",
					   mods & MouseMods::alt ? "alt" : "");
};

std::string MouseMoveEvent::toString() const {
	return fmt::format("MouseMoveEvent{{x:{}, y:{}}}", pos.x, pos.y);
};