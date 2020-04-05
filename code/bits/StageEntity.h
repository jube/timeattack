#ifndef STAGE_ENTITY_H
#define STAGE_ENTITY_H

#include <gf/Entity.h>

namespace ta {

  struct TimeAttackData;
  struct TimeAttackState;

  class StageEntity : public gf::Entity {
  public:
    enum Which {
      Current,
      Previous,
    };

    StageEntity(TimeAttackData& data, const TimeAttackState& state, Which which = Current);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    TimeAttackData& m_data;
    const TimeAttackState& m_state;
    Which m_which;
  };



}

#endif // STAGE_ENTITY_H
