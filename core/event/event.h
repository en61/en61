#pragma once

namespace en61 {

enum EventType {
	MouseMoved,
	MouseScrolled,
	KeyPressed,
	FramebufferResized
};

class Event {
public:
	virtual EventType GetType() const = 0;
	virtual const char *GetName() const = 0;
};

class EventDispatcher {
public:
	EventDispatcher(Event &event)
		: _event(event) { }

	template <class _Event, class _HandleFunc>
	bool Register(const _HandleFunc &func) {
		if (_event.GetType() == _Event::GetStaticType()) {
			func(static_cast<_Event&>(_event));
			return true;
		}
		return false;
	}

private:
	Event &_event;
};

#define BIND_EVENT_FN(fn) [this](auto&& ...args) -> decltype(auto) { \
	return this->fn(std::forward<decltype(args)>(args)...); \
}

#define META_EVENT_CLASS(type) \
	public: \
		static EventType GetStaticType() { return EventType::type; } \
		virtual EventType GetType() const override { return GetStaticType(); } \
		virtual const char *GetName() const override { return #type; }

} // namespace en61
