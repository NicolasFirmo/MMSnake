#pragma once

#include "event.h"

#include "utility/point.hpp"

enum MouseButton {
	left   = 0,
	right  = 1,
	middle = 2
};

enum MouseAction {
	released = 0,
	pressed	 = 1
};

enum MouseMods {
	none		 = 0b000,
	shift		 = 0b001,
	ctrl		 = 0b010,
	shiftCtrl	 = 0b011,
	alt			 = 0b100,
	shiftAlt	 = 0b101,
	ctrlAlt		 = 0b110,
	shiftCtrlAlt = 0b111,
};

struct MouseButtonEvent : public Event {
	MouseButtonEvent(MouseButton button, MouseAction action, MouseMods mods)
		: button(button),
		  action(action),
		  mods(mods) {}

	[[nodiscard]] Type getType() const override { return Type::mouseButton; };

	MouseButton button;
	MouseAction action;
	MouseMods mods;
};

struct MouseMoveEvent : public Event {
	MouseMoveEvent(Point2<double> pos) : pos(pos) {}

	[[nodiscard]] Type getType() const override { return Type::mouseMove; };

	Point2<double> pos;
};
