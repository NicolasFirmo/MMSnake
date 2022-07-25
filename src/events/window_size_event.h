#pragma once

#include "event.h"
#include "utility/size.hpp"

struct WindowSizeEvent : public Event {
	WindowSizeEvent(Size2<int> size) : size(size) {}

	[[nodiscard]] Type getType() const override { return Type::windowSize; };

	Size2<int> size;
};
