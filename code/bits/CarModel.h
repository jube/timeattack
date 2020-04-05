#ifndef TA_CAR_MODEL_H
#define TA_CAR_MODEL_H

#include <gf/Model.h>
#include <gf/Vector.h>

namespace ta {
  struct TimeAttackState;

  class CarModel : public gf::Model {
  public:
    CarModel(TimeAttackState& state);

    void createAttractionFrom(gf::Vector2f position);
    void disableAttraction();

    void update(gf::Time time) override;

  private:
    TimeAttackState& m_state;
    bool m_attract;
    gf::Vector2f m_attractionOrigin;
  };

}

#endif // TA_CAR_MODEL_H
