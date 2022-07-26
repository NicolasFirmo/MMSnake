#pragma once

struct Event {
	enum class Type { windowSize, mouseButton, mouseMove };

	[[nodiscard]] virtual Type getType() const = 0;

	Event() = default;
	virtual ~Event() {}
	Event(const Event &) = default;
	Event(Event &&) = default;
	Event &operator=(const Event &) = default;
	Event &operator=(Event &&) = default;
};