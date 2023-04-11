#pragma once

#include <core/event/event.h>

namespace en61 {

class KeyPressedEvent: public Event {
	META_EVENT_CLASS(KeyPressed)

public:
	KeyPressedEvent(int keycode)
		: _keycode(keycode) { }

	int GetKeycode() const { return _keycode; }

private:
	int _keycode;
};

} // namespace en61
