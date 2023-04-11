#pragma once

#include <core/event/event.h>

namespace en61 {

class MouseMovedEvent: public Event {
	META_EVENT_CLASS(MouseMoved)

public:
	MouseMovedEvent(double x, double y)
		: _x(x), _y(y) { }

	double GetX() const { return _x; }
	double GetY() const { return _y; }

private:
	double _x, _y;
};

class MouseScrolledEvent: public Event {
	META_EVENT_CLASS(MouseScrolled)

public:
	MouseScrolledEvent(double x_offset, double y_offset)
		: _x_offset(x_offset), _y_offset(y_offset) { }

	double GetXOffset() const { return _x_offset; }
	double GetYOffset() const { return _y_offset; }

private:
	double _x_offset, _y_offset;
};

} // namespace en61
