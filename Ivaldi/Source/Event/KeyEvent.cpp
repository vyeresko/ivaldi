#include "Precompiled.h"
#include "KeyEvent.h"


namespace ivaldi {
	KeyEvent::KeyEvent(KeyEvent::KeyCode code)
		: m_key_code(code)
	{}

	KeyDown::KeyDown(KeyEvent::KeyCode code, bool repeat)
		: KeyEvent::KeyEvent(code), m_repeat(repeat)
	{}
	
	KeyUp::KeyUp(KeyEvent::KeyCode code)
		: KeyEvent::KeyEvent(code)
	{}

	
}
