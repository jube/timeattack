#ifndef TA_CHRONO_MODEL_H
#define TA_CHRONO_MODEL_H

#include <vector>

#include <gf/Model.h>
#include <gf/Time.h>

namespace ta {

  class ChronoModel : public gf::Model {
  public:
    void startRace();
    void startStage();

    const std::vector<gf::Time>& getTimes() const;

    void update(gf::Time time) override;

  private:
    std::vector<gf::Time> m_times;
  };


}


#endif // TA_CHRONO_MODEL_H
