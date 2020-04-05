#include "MouseTracker.h"

namespace ta {

  MouseTracker::MouseTracker()
  : m_buttonPressed(false)
  {
  }

  void MouseTracker::processEvent(const gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseButtonPressed:
        if (event.mouseButton.button == gf::MouseButton::Left) {
          m_position = event.mouseButton.coords;
          m_buttonPressed = true;
        };
        break;

      case gf::EventType::MouseButtonReleased:
        if (event.mouseButton.button == gf::MouseButton::Left) {
          m_position = event.mouseButton.coords;
          m_buttonPressed = false;
        };
        break;

      case gf::EventType::MouseMoved:
        if (m_buttonPressed) {
          m_position = event.mouseCursor.coords;
        }
        break;

      default:
        break;
    }
  }

  bool MouseTracker::isActive() const {
    return m_buttonPressed;
  }

  gf::Vector2i MouseTracker::getLastPosition() const {
    return m_position;
  }

  void MouseTracker::reset() {
    m_buttonPressed = false;
  }

}
