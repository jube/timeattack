#include "ChronoModel.h"

#include <cassert>

namespace ta {

  void ChronoModel::startRace() {
    m_times.clear();
  }

  void ChronoModel::startStage() {
    m_times.push_back(gf::Time::zero());
  }

  const std::vector<gf::Time>& ChronoModel::getTimes() const {
    return m_times;
  }

  void ChronoModel::update(gf::Time time) {
    assert(!m_times.empty());
    m_times.back() += time;
  }

}
