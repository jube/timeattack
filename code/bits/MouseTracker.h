#ifndef TA_MOUSE_TRACKER_H
#define TA_MOUSE_TRACKER_H

#include <gf/Event.h>
#include <gf/Vector.h>

namespace ta {

  class MouseTracker {
  public:
    MouseTracker();

    void processEvent(const gf::Event& event);

    bool isActive() const;
    gf::Vector2i getLastPosition() const;
    void reset();

  private:
    bool m_buttonPressed;
    gf::Vector2i m_position;
  };

}

#endif // TA_MOUSE_TRACKER_H
