#include "TimerModel.h"

#include <algorithm>

namespace ta {

  namespace {
    constexpr gf::Time MaxTime = gf::seconds(60);
  }

  TimerModel::TimerModel()
  : m_running(false)
  {
  }

  void TimerModel::reset(gf::Time time) {
    m_running = false;
    m_remaining = time;
  }

  void TimerModel::addTime(gf::Time time) {
    m_remaining += time;
    m_remaining = std::min(m_remaining, MaxTime);
  }

  bool TimerModel::isFinished() const {
    return m_remaining < gf::Time::zero();
  }

  gf::Time TimerModel::getRemainingTime() const {
    return m_remaining;
  }

  void TimerModel::pause() {
    m_running = false;
  }

  void TimerModel::resume() {
    m_running = true;
  }

  void TimerModel::update(gf::Time time) {
    m_remaining -= time;
  }

}
