#ifndef TA_TIMER_MODEL_H
#define TA_TIMER_MODEL_H

#include <gf/Model.h>

namespace ta {

  class TimerModel : public gf::Model {
  public:
    TimerModel();

    void reset(gf::Time time);
    void addTime(gf::Time time);
    bool isFinished() const;
    gf::Time getRemainingTime() const;

    void pause();
    void resume();

    void update(gf::Time time) override;

  private:
    bool m_running;
    gf::Time m_remaining;
  };


}


#endif // TA_TIMER_MODEL_H
