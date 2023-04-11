#pragma once

#include <core/event/event.h>

namespace en61 {

class FramebufferResizedEvent: public Event {
	META_EVENT_CLASS(FramebufferResized)

public:
	FramebufferResizedEvent(int width, int height)
		: _width(width), _height(height) { }

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

private:
	int _width, _height;
};

} // namespace en61
