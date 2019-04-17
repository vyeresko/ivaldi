#pragma once

#include "Event/Event.h"

namespace ivaldi {
	class IVALDI_API KeyEvent: public Event {
	public:
		using KeyCode = int;

		KeyCode getKeyCode() const { return m_key_code; }

	protected:
		KeyEvent(KeyCode code);
		~KeyEvent() = default;

	private:
		int m_key_code;
	};

	class KeyDown: public KeyEvent {
	public:
		KeyDown(KeyCode code, bool repeat);
		~KeyDown() = default;

		bool isRepeat() { return m_repeat; }
		const char* getName() const override { return "KeyDown"; }
		Event::EventType getType() const override { return Event::EventType::KeyDown; }
	
	private:
		bool m_repeat = false;
	};

	class KeyUp : public KeyEvent {
	public:
		KeyUp(KeyCode code);
		~KeyUp() = default;

		const char* getName() const override { return "KeyUp"; }
		Event::EventType getType() const override { return Event::EventType::KeyUp; }
	};
}