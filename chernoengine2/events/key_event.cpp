//
// Created by shepherd on 8.3.23.
//

#include <chernoengine2/events/key_event.hpp>

#include <sstream>

namespace chernoengine2 {

KeyEvent::KeyEvent(int key_code) : key_code_(key_code) {

}

int KeyEvent::GetKeyCode() const {
    return key_code_;
}

KeyPressedEvent::KeyPressedEvent(int key_code, bool repeat) : KeyEvent(key_code), repeat_(repeat) {}

bool KeyPressedEvent::IsRepeat() const {
    return repeat_;
}

std::string KeyPressedEvent::ToString() const {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key_code_ << " (repeat = " << IsRepeat() << ")\n";
    return ss.str();
}

KeyReleasedEvent::KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

std::string KeyReleasedEvent::ToString() const {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << key_code_ << '\n';
    return ss.str();
}

KeyTypedEvent::KeyTypedEvent(int key_code) : KeyEvent(key_code) {}

std::string KeyTypedEvent::ToString() const {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << key_code_ << '\n';
    return ss.str();
}

} // chernoengine2